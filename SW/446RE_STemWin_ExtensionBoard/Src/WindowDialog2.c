/*
 * WindowDialog2.c
 *
 *  Created on: 2019. aug. 26.
 *      Author: David
 */
#include "DIALOG.h"
#include <stdio.h>
#include "ExtensionBoard.h"
/*********************************************************************
*
*       Externals
*
**********************************************************************
*/

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0    (GUI_ID_USER + 0x00)
#define ID_TEXT_1    (GUI_ID_USER + 0x01)
#define ID_TEXT_2    (GUI_ID_USER + 0x02)
#define ID_PROGBAR    (GUI_ID_USER + 0x03)
/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       Variables
*
**********************************************************************
*/
	char str[1000];
	float LM75Temp;
	float BME280Temp;
	float BME280Humidity;
	float BME280Pressure;
	uint32_t TEMT6000;
	U8 IOdata;
	U8 ProgbarData;
	extern MPU6050 mpu1;
	U8 CounterData=0;
/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 400, 240, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text_1", ID_TEXT_1, 0, 0, 300, 100, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Text_2", ID_TEXT_2, 300, 0, 100, 100, 0, 0x0, 0 },
  {PROGBAR_CreateIndirect, "Progbar", ID_PROGBAR, 10,170, 380,40,0,0,0 }
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;

  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    //
    // Initialization of 'Text_P'
    //
	//text1
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
    //TEXT_SetFont(hItem,GUI_FONT_D64);
    TEXT_SetTextColor(hItem,GUI_WHITE);
    TEXT_SetBkColor(hItem,GUI_BLACK);
    GUI_SetTextMode(GUI_TM_NORMAL);
	//text2
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetTextAlign(hItem, GUI_TA_RIGHT | GUI_TA_VCENTER);
    TEXT_SetFont(hItem,GUI_FONT_D64);
    TEXT_SetTextColor(hItem,GUI_YELLOW);
    TEXT_SetBkColor(hItem,GUI_BLACK);
    GUI_SetTextMode(GUI_TM_NORMAL);
    //progbar
    hItem = WM_GetDialogItem(pMsg->hWin, ID_PROGBAR);
    PROGBAR_SetText(hItem, "");
	PROGBAR_SKINFLEX_PROPS pProps;
	PROGBAR_GetSkinFlexProps(&pProps,0);
	pProps.aColorLowerL[0]=0x0029D4;//
	pProps.aColorLowerL[1]=0x1C33E2;//
	pProps.aColorUpperL[0]=0xCDCDFF;//
	pProps.aColorUpperL[1]=0x9CACEE;//
	PROGBAR_SetSkinFlexProps(&pProps,0);
    break;
  case WM_PAINT:
	    GUI_SetBkColor(GUI_BLACK);
	    GUI_Clear();
	    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
	    //TEXT_SetTextAlign(hItem, GUI_TA_LEFT | GUI_TA_VCENTER);
	    //TEXT_SetFont(hItem,GUI_FONT_D64);
	    //TEXT_SetTextColor(hItem,GUI_WHITE);
	    TEXT_SetBkColor(hItem,GUI_BLACK);
	    GUI_SetTextMode(GUI_TM_NORMAL);
	  break;
  default:
	WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       _cbBk
*/
static void _cbBk(WM_MESSAGE * pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    break;
  default:
    WM_DefaultProc(pMsg);
    break;
  }
}


/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
	//local variables
  WM_HWIN hDialog;
  WM_HWIN hText_1;
  WM_HWIN hText_2;
  WM_HWIN hProgBar;

  GUI_Init();//initialization
  WM_SetDesktopColor(GUI_BLACK);
  GUI_SetBkColor(GUI_BLACK);
  GUI_Clear();

  WM_SetCallback(WM_HBKWIN, _cbBk);
  hDialog  = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
  hText_1 = WM_GetDialogItem(hDialog, ID_TEXT_1);
  hText_2 = WM_GetDialogItem(hDialog, ID_TEXT_2);
  hProgBar=WM_GetDialogItem(hDialog,ID_PROGBAR);
  WM_EnableMemdev(hDialog);//enabling memory devices
  //Value = 0;
  while (1) {
	//LM75
	LM75Temp=ReadLM75();
	//BME280
	BME280Temp = BME280_ReadTemperature();
	BME280Humidity=BME280_ReadHumidity();
	BME280Pressure=BME280_ReadPressure();
	//MPU6050
	MPU6050_ReadTemperature(&mpu1);
	MPU6050_ReadAll(&mpu1);
	//On chip temp sensor
	//TODO
	//TEMT6000 LightSensor
	if (HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK){//analog read
		TEMT6000 = HAL_ADC_GetValue(&hadc1);
	}
	//Write to string
	sprintf(str,
			"LM75 Temp=%.1f °C\r\n"
			"BME280: Temp=%.2f °C, Humidity=%.2f, Pressure=%.2f\r\n"
			"MPU6050 Accelerometer: X=%d, Y=%d, Z=%d\r\n"
			"MPU6050 Temp=%.2f °C\r\n"
			"MPU6050 Gyroscope: X=%d, Y=%d, Z=%d\r\n"
			"TEMT6000 LightSensor ADC=%u\r\n"
			,LM75Temp
			,BME280Temp, BME280Humidity, BME280Pressure/1000
			,mpu1.Accelerometer_X,mpu1.Accelerometer_Y,mpu1.Accelerometer_Z
			,mpu1.Temperature
			,mpu1.Gyroscope_X,mpu1.Gyroscope_Y,mpu1.Gyroscope_Z
			,(uint16_t)TEMT6000
			);
	TEXT_SetText(hText_1, str);//displaying string
	CounterData++;
	if(CounterData==100){
		CounterData=0;
	}
	sprintf(str,"%u",CounterData);
	TEXT_SetText(hText_2, str);//displaying counter
	PROGBAR_SetValue(hProgBar, ProgbarData);//displaying progressbar
    GUI_Delay(500);
	if(TIM3->CNT<0x7FFF){
		TIM3->CNT=0x7FFF;
	}
	if(TIM3->CNT>0x8063){
		TIM3->CNT=0x8063;
	}
	ProgbarData=TIM3->CNT-0x7FFF;

	IOdata=~ReadIOExpander();
	if(IOdata&0x01){
		SetBackLightPWM(100);
	}
	if(IOdata&0x02){
		WriteIOExpander(0x40);
	}
	if(IOdata&0x04){
		WriteIOExpander(0x20);
	}
	if(IOdata&0x08){
		SetBackLightPWM(0);
	}
	if(!(IOdata&0x80)){
		SetBackLightPWM(100);
	}
  }
}

/*************************** End of file ****************************/

