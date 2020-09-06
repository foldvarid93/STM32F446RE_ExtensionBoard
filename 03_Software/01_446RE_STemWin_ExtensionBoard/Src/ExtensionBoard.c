/*********************************************************************/
#include "ExtensionBoard.h"
/*********************************************************************/
//Author: Dávid Földvári
//github: foldvarid93
//Version: 1.0
//HW Version: 1.0
/*********************************************************************/
//global variables
/*********************************************************************/
MPU6050 mpu1;
uint8_t u;
/*********************************************************************/
//board initialization
/*********************************************************************/
void BoardInit(void){
	//Gpio
	MX_GPIO_Init();
	//Timer
	InitEncoder();//initialize encoder input and timer
	InitPWM();//LCD backlight and H-bridge PWM init
	SetHBridgePWM(100);//H bridge PWM signal
	//I2C
	MX_I2C3_Init();//init I2C3 I2C peripheral
	InitPCF8574();//init port extension I2C slave
	BME280_Init();//init BME280 pressure humidity and temerature sensor
	InitMPU6050();//init MPU6050 gyro sensor
	//SPI

	//LCD
	MX_CRC_Init();//need for GUI
	GUI_Init();//init gui
	GUI_Clear();//clear screen
	SetBackLightPWM(100);//Backlight PWM max
	//Analog
	MX_ADC1_Init();//Init all analog inputs
	HAL_ADC_Start(&hadc1);//start ADC
	//init light sensor analog input
	//init operational amplifier analog input

	//Uart
	MX_USART2_UART_Init();//PC UART
	MX_USART3_UART_Init();//ESP8266UART
	//init esp8266
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	ESP_Init("foldvarid93","19701971");
	Server_Start();
	//
	RemoteXY_Init();
	while(1){
		//RemoteXY_Handler();
	}
}
/*********************************************************************/
//Timer
/*********************************************************************/
void InitEncoder(void){
	MX_TIM3_Init();
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	TIM3->CNT=0x7FFF;
}
/*********************************************************************/
void InitPWM(void){
	MX_TIM2_Init();
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1|TIM_CHANNEL_2);
}
/*********************************************************************/
void SetBackLightPWM(uint16_t value){
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}
/*********************************************************************/
void SetHBridgePWM(uint16_t value){
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
/*********************************************************************/
/*********************************************************************/
//I2C
/*********************************************************************/
void InitPCF8574(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitStruct.Pin = INT_PE_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(INT_PE_GPIO_Port, &GPIO_InitStruct);//PA0 external interrupt input falling edge
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 15);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);//EXTI interrupt init

	uint8_t data=0B10011111;
	HAL_I2C_Master_Transmit(&hi2c3,0x40,&data,1,100);
}
/*********************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if (GPIO_Pin==INT_PE_Pin){
		ReadIOExpander();
	}
	if (GPIO_Pin==INT_AG_Pin){
		asm("nop");
	}
}
/*********************************************************************/
uint8_t ReadIOExpander(void){
	uint8_t data;
	HAL_I2C_Master_Receive(&hi2c3,0x41,&data,1,100);
	return data;
}
/*********************************************************************/
void WriteIOExpander(uint8_t value){
	uint8_t data=value;
	data|=0B10011111;
	HAL_I2C_Master_Transmit(&hi2c3,0x40,&data,1,100);
}
/*********************************************************************/
void InitMPU6050(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	GPIO_InitStruct.Pin = INT_AG_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(INT_AG_GPIO_Port, &GPIO_InitStruct);//PC13 external interrupt input falling edge
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 15);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);//EXTI interrupt init
	MPU6050_Init(&mpu1,MPU6050_Accelerometer_2G,MPU6050_Gyroscope_250s );
	MPU6050_DisableInterrupts(&mpu1);
}
/*********************************************************************/
uint16_t InitLM75(void){
	uint8_t data[2];
	HAL_I2C_Master_Transmit(&hi2c3,0x90,0x00,1,100);
	HAL_I2C_Master_Receive(&hi2c3,0x91,data,2,100);
	uint16_t retval =((data[0]<<8) & 0xFF00);
	retval|=data[1];
	return retval;
}
/*********************************************************************/
float ReadLM75(void){
	float LM75Temp;
	uint8_t data[2];
	HAL_I2C_Master_Receive(&hi2c3,0x91,data,2,100);
	uint8_t szorzo;
	szorzo=data[1]&0x80;
	szorzo>>=7;
	LM75Temp=0.5*szorzo;
	LM75Temp+=data[0]&0x7F;
	if(data[0]&0x80){//negative temperature
		//Array[5]='-';
		LM75Temp*=-1;
	}
	return LM75Temp;
	/*
	else{//positive temperature
		Array[5]='+';
	}
	if(data[0]/100){//if greater than 100°C
		Array[6]=(data[0]/100)+'0';//hundreds
	}
	else{
		Array[6]=' ';//else space
	}
	data[0]%=100;//modulo100
	Array[7]=(data[0]/10)+'0';//tens
	data[0]%=10;//modulo10
	Array[8]=(data[0])+'0';//singles
	Array[9]=',';//comma
	if(data[1]&0x80){//if there is ,5°C at the end
		Array[10]='5';
	}
	else{
		Array[10]='0';//else 0
	}*/
}
/*********************************************************************/
//SPI
/*********************************************************************/
void ShiftRegister4094(void){

}
/*********************************************************************/
/*********************************************************************/
//Analog
/*********************************************************************/
void LightSensorTEMT6000(void){

}
/*********************************************************************/
void CurrentSensorACS712(void){

}
/*********************************************************************/
void CurrentSensorVNH7100BAS(void){

}
/*********************************************************************/
/*********************************************************************/
//UART
/*********************************************************************/
void ESP8266(void){

}
/*********************************************************************/
