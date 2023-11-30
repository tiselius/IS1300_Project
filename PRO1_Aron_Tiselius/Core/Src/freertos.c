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
#include "functions.h"
#include "variables.h"
#include "semphr.h"
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
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for SecondTask */
osThreadId_t SecondTaskHandle;
const osThreadAttr_t SecondTask_attributes = {
  .name = "SecondTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for mutex01 */
osMutexId_t mutex01Handle;
const osMutexAttr_t mutex01_attributes = {
  .name = "mutex01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void Second(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of mutex01 */
  mutex01Handle = osMutexNew(&mutex01_attributes);

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of SecondTask */
  SecondTaskHandle = osThreadNew(Second, NULL, &SecondTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(2200) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	for(;;)
	{
		// Obtain the semaphore - wait 10 ticks
		if( xSemaphoreTake( mutex01Handle, ( TickType_t ) 10 )== pdTRUE )
		{
			// We now have the semaphore and can access the shared resource.

			/*CRITICAL REGION BEGINS*/
			setLeds(L1_Red);
			setLeds(L1_Green);
			HAL_Delay(1000);

			/*CRITICAL REGION ENDS*/
			if( xSemaphoreGive( mutex01Handle ) == pdTRUE )
			{
				setLeds(L3_Red);
				setLeds(L3_Green);
				HAL_Delay(1000); 		/*LAMPORNA BETYDER WOOHOO VI GAV TILLBAKA DEN :))))))*/
				// We would not expect this call to fail because we must have
				// obtained the semaphore to get here.
				resetLeds(0xFFFFFF);
			}
			  vTaskDelayUntil( &xLastWakeTime, xPeriod );
		}
	}

  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Second */
/**
* @brief Function implementing the SecondTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Second */
void Second(void *argument)
{
  /* USER CODE BEGIN Second */

	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(500) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  setLeds(L2_Red + L4_Red);
	  HAL_Delay(300);
	  resetLeds(L2_Red + L4_Red);
	  vTaskDelayUntil( &xLastWakeTime, xPeriod );
  }
  /* USER CODE END Second */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

