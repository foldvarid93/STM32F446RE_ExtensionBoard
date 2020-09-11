/*********************************************************************/
#ifndef EXTENSIONBOARD_H
#define EXTENSIONBOARD_H
/*********************************************************************/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "crc.h"
#include "adc.h"
#include "usart.h"
#include "gpio.h"
#include "GUI.h"
#include "S6D04D1.h"
#include "BME280.h"
#include "MPU6050.h"
#include "ESP8266_HAL.h"
#include "UartRingbuffer_multi.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include "remotexy.h"
/*********************************************************************/
void BoardInit(void);
void InitEncoder(void);
void InitPWM(void);
uint8_t ReadIOExpander(void);
void WriteIOExpander(uint8_t);
void SetBackLightPWM(uint16_t);
void SetHBridgePWM(uint16_t);
void InitPCF8574(void);
uint16_t InitLM75(void);
float ReadLM75(void);
void InitMPU6050(void);
/*********************************************************************/
#endif
/*********************************************************************/
