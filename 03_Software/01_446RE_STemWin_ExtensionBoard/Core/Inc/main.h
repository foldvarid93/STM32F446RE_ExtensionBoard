/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define INT_PE_Pin_Pin GPIO_PIN_0
#define INT_PE_Pin_GPIO_Port GPIOA
#define INT_PE_Pin_EXTI_IRQn EXTI0_IRQn
#define HB_PWM_Pin_Pin GPIO_PIN_1
#define HB_PWM_Pin_GPIO_Port GPIOA
#define USART_TX_Pin_Pin GPIO_PIN_2
#define USART_TX_Pin_GPIO_Port GPIOA
#define USART_RX_Pin_Pin GPIO_PIN_3
#define USART_RX_Pin_GPIO_Port GPIOA
#define HB_CS_Pin_Pin GPIO_PIN_4
#define HB_CS_Pin_GPIO_Port GPIOA
#define LD2_Pin_Pin GPIO_PIN_5
#define LD2_Pin_GPIO_Port GPIOA
#define ENC_A_Pin_Pin GPIO_PIN_6
#define ENC_A_Pin_GPIO_Port GPIOA
#define ENC_B_Pin_Pin GPIO_PIN_7
#define ENC_B_Pin_GPIO_Port GPIOA
#define DB0_Pin_Pin GPIO_PIN_0
#define DB0_Pin_GPIO_Port GPIOB
#define DB1_Pin_Pin GPIO_PIN_1
#define DB1_Pin_GPIO_Port GPIOB
#define DB2_Pin_Pin GPIO_PIN_2
#define DB2_Pin_GPIO_Port GPIOB
#define WR_Pin_Pin GPIO_PIN_10
#define WR_Pin_GPIO_Port GPIOB
#define CD_Pin_Pin GPIO_PIN_12
#define CD_Pin_GPIO_Port GPIOB
#define RST_Pin_Pin GPIO_PIN_13
#define RST_Pin_GPIO_Port GPIOB
#define SPI_CS1_Pin_Pin GPIO_PIN_9
#define SPI_CS1_Pin_GPIO_Port GPIOA
#define SHR_STR_Pin_Pin GPIO_PIN_11
#define SHR_STR_Pin_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWDCLK_Pin GPIO_PIN_14
#define SWDCLK_GPIO_Port GPIOA
#define DB3_Pin_Pin GPIO_PIN_3
#define DB3_Pin_GPIO_Port GPIOB
#define DB4_Pin_Pin GPIO_PIN_4
#define DB4_Pin_GPIO_Port GPIOB
#define DB5_Pin_Pin GPIO_PIN_5
#define DB5_Pin_GPIO_Port GPIOB
#define D6B_Pin_Pin GPIO_PIN_6
#define D6B_Pin_GPIO_Port GPIOB
#define DB7_Pin_Pin GPIO_PIN_7
#define DB7_Pin_GPIO_Port GPIOB
#define RD_Pin_Pin GPIO_PIN_8
#define RD_Pin_GPIO_Port GPIOB
#define CS_Pin_Pin GPIO_PIN_9
#define CS_Pin_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
