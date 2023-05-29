/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ExtensionBoard.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId InitTaskHandle;
osThreadId MainTaskHandle;
osThreadId GUI_TaskHandle;
osThreadId InterruptTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void InitTask_Func(void const * argument);
void MainTask_Func(void const * argument);
void GUI_Task_Function(void const * argument);
void InterruptTask_Func(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of InitTask */
  osThreadDef(InitTask, InitTask_Func, osPriorityNormal, 0, 128);
  InitTaskHandle = osThreadCreate(osThread(InitTask), NULL);

  /* definition and creation of MainTask */
  osThreadDef(MainTask, MainTask_Func, osPriorityNormal, 0, 512);
  MainTaskHandle = osThreadCreate(osThread(MainTask), NULL);

  /* definition and creation of GUI_Task */
  osThreadDef(GUI_Task, GUI_Task_Function, osPriorityIdle, 0, 2048);
  GUI_TaskHandle = osThreadCreate(osThread(GUI_Task), NULL);

  /* definition and creation of InterruptTask */
  osThreadDef(InterruptTask, InterruptTask_Func, osPriorityIdle, 0, 256);
  InterruptTaskHandle = osThreadCreate(osThread(InterruptTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_InitTask_Func */
/**
  * @brief  Function implementing the InitTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_InitTask_Func */
void InitTask_Func(void const * argument)
{
  /* USER CODE BEGIN InitTask_Func */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END InitTask_Func */
}

/* USER CODE BEGIN Header_MainTask_Func */
/**
* @brief Function implementing the MainTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MainTask_Func */
void MainTask_Func(void const * argument)
{
  /* USER CODE BEGIN MainTask_Func */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END MainTask_Func */
}

/* USER CODE BEGIN Header_GUI_Task_Function */
/**
* @brief Function implementing the GUI_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GUI_Task_Function */
void GUI_Task_Function(void const * argument)
{
  /* USER CODE BEGIN GUI_Task_Function */
	BoardInit();
  /* Infinite loop */
  for(;;)
  {
	  MainTask();
    osDelay(80);
  }
  /* USER CODE END GUI_Task_Function */
}

/* USER CODE BEGIN Header_InterruptTask_Func */
/**
* @brief Function implementing the InterruptTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_InterruptTask_Func */
void InterruptTask_Func(void const * argument)
{
  /* USER CODE BEGIN InterruptTask_Func */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END InterruptTask_Func */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
