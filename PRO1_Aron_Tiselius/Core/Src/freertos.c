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
#include "variables.h"
#include "functions.h"
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
/* Definitions for IdleTrafficTask */
osThreadId_t IdleTrafficTaskHandle;
const osThreadAttr_t IdleTrafficTask_attributes = {
  .name = "IdleTrafficTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for PedCrossNSTask */
osThreadId_t PedCrossNSTaskHandle;
const osThreadAttr_t PedCrossNSTask_attributes = {
  .name = "PedCrossNSTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TrafficContNSTa */
osThreadId_t TrafficContNSTaHandle;
const osThreadAttr_t TrafficContNSTa_attributes = {
  .name = "TrafficContNSTa",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TrafficContEWTa */
osThreadId_t TrafficContEWTaHandle;
const osThreadAttr_t TrafficContEWTa_attributes = {
  .name = "TrafficContEWTa",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for PedCrossEWTask */
osThreadId_t PedCrossEWTaskHandle;
const osThreadAttr_t PedCrossEWTask_attributes = {
  .name = "PedCrossEWTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for NSBlueTask */
osThreadId_t NSBlueTaskHandle;
const osThreadAttr_t NSBlueTask_attributes = {
  .name = "NSBlueTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for EWBlueTask */
osThreadId_t EWBlueTaskHandle;
const osThreadAttr_t EWBlueTask_attributes = {
  .name = "EWBlueTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for FourWay */
osMutexId_t FourWayHandle;
const osMutexAttr_t FourWay_attributes = {
  .name = "FourWay"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void IdleTraffic(void *argument);
void PedCrossNS(void *argument);
void TrafficContNS(void *argument);
void TrafficContEW(void *argument);
void PedCrossEW(void *argument);
void NSBlue(void *argument);
void EWBlue(void *argument);

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
  /* creation of FourWay */
  FourWayHandle = osMutexNew(&FourWay_attributes);

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

  /* creation of IdleTrafficTask */
  IdleTrafficTaskHandle = osThreadNew(IdleTraffic, NULL, &IdleTrafficTask_attributes);

  /* creation of PedCrossNSTask */
  PedCrossNSTaskHandle = osThreadNew(PedCrossNS, NULL, &PedCrossNSTask_attributes);

  /* creation of TrafficContNSTa */
  TrafficContNSTaHandle = osThreadNew(TrafficContNS, NULL, &TrafficContNSTa_attributes);

  /* creation of TrafficContEWTa */
  TrafficContEWTaHandle = osThreadNew(TrafficContEW, NULL, &TrafficContEWTa_attributes);

  /* creation of PedCrossEWTask */
  PedCrossEWTaskHandle = osThreadNew(PedCrossEW, NULL, &PedCrossEWTask_attributes);

  /* creation of NSBlueTask */
  NSBlueTaskHandle = osThreadNew(NSBlue, NULL, &NSBlueTask_attributes);

  /* creation of EWBlueTask */
  EWBlueTaskHandle = osThreadNew(EWBlue, NULL, &EWBlueTask_attributes);

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
	/* Infinite loop */
	for(;;)
	{
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_IdleTraffic */
/**
 * @brief IdleTraffic implements the requirement R2.4.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_IdleTraffic */
void IdleTraffic(void *argument)
{
  /* USER CODE BEGIN IdleTraffic */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(100) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();


	/* Infinite loop */
	for(;;)
	{
		if(!(TL1_Car_Flag || TL3_Car_Flag) && !(TL2_Car_Flag || TL4_Car_Flag)){ //No cars
			if(EWTrafficFlag){ //Traffic is allowed EW
				/*Change the trafic to NS, delay greenDelay*/
				xSemaphoreTake( FourWayHandle, portMAX_DELAY);

				pedestrianOffEW();
				pedestrianOffNS();

				trafficTransition();
				trafficOnNS();
				trafficOffEW();
				pedestrianOnNS();

				xSemaphoreGive(FourWayHandle);
				vTaskDelay(pdMS_TO_TICKS(greenDelay));
			}
			else{//Traffic is allowed NS
				/*Change the trafic to EW, delay greenDelay*/
				xSemaphoreTake( FourWayHandle, portMAX_DELAY);
				pedestrianOffEW();
				pedestrianOffNS();

				trafficTransition();
				trafficOnEW();
				trafficOffNS();
				pedestrianOnEW();

				xSemaphoreGive(FourWayHandle);
				vTaskDelay(pdMS_TO_TICKS(greenDelay));
			}
		}

		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END IdleTraffic */
}

/* USER CODE BEGIN Header_PedCrossNS */
/**
 * @brief PedCrossNS handles the NS pedestrian crossing events.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_PedCrossNS */
void PedCrossNS(void *argument)
{
  /* USER CODE BEGIN PedCrossNS */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(50) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
		if(PL1_Switch_Flag){ //Button has been pressed.
			if(!NSPedestrianFlag){ //The light is not already green
				while(NSPedTransitioning){ //Wait if the lights are transitioning. It causes trouble otherwise.
					osDelay(1);
				}
				if(!NSPedestrianFlag){ //After the delay the light might have turned green. Check again.
					while(!NSTrafficFlag){ //Waits for NS traffic to turn green.
						osDelay(1);
					}
					xSemaphoreTake(FourWayHandle, portMAX_DELAY);
					/*Makes the light green and resets the flag.*/
					pedestrianOnNS();
					pedestrianOffEW();
					PL1_Switch_Flag = 0;

					vTaskDelay(pdMS_TO_TICKS(walkingDelay));
					xSemaphoreGive(FourWayHandle);
				}
			}
			PL1_Switch_Flag = 0; //Resets the flag even if the light wasn't changed.
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END PedCrossNS */
}

/* USER CODE BEGIN Header_TrafficContNS */
/**
 * @brief TrafficContNS handles light behavior when there is a car NS.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TrafficContNS */
void TrafficContNS(void *argument)
{
  /* USER CODE BEGIN TrafficContNS */
	trafficOnEW();
	trafficOffNS();

	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(50) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();  /* Infinite loop */

	for(;;)
	{
		if(TL2_Car_Flag || TL4_Car_Flag){ //There is a car NS.
			if(EWTrafficFlag){	//Current traffic light is EW.
				if((TL1_Car_Flag || TL3_Car_Flag)) {	//If there's a car EW we have to wait.
					vTaskDelay(pdMS_TO_TICKS(redDelayMax));
					if(!PL2_Switch_Flag){ //No overlapping pedestrian crossing
						xSemaphoreTake( FourWayHandle, portMAX_DELAY);
						/*Transition NS to green, EW to red.*/
						pedestrianOffEW();
						pedestrianOffNS();

						trafficTransition();
						trafficOnNS();
						trafficOffEW();
						pedestrianOnNS();
						xSemaphoreGive(FourWayHandle);
					}
				}
				else{									//If there is no car EW, just go.
					if(!PL2_Switch_Flag){ //No overlapping pedestrian crossing
						xSemaphoreTake( FourWayHandle, portMAX_DELAY);
						/*Transition NS to green, EW to red.*/

						pedestrianOffEW();
						pedestrianOffNS();

						trafficTransition();
						trafficOnNS();
						trafficOffEW();
						pedestrianOnNS();
						xSemaphoreGive(FourWayHandle);
					}
				}
			}
			else if(!PL2_Switch_Flag){ //Light is already green and no active pedestrian crossing causing overlap
				osDelay(1);
			}
			else{ //Light is already green, but there is an active pedestrian crossing.
				xSemaphoreTake( FourWayHandle, portMAX_DELAY);
				/*Transition EW to green, NS to red.*/
				pedestrianOffEW();
				pedestrianOffNS();

				trafficTransition();
				trafficOnEW();
				trafficOffNS();
				pedestrianOnEW();
				xSemaphoreGive(FourWayHandle);
			}
		}

		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}

  /* USER CODE END TrafficContNS */
}

/* USER CODE BEGIN Header_TrafficContEW */
/**
 * @brief TrafficContEW handles light behavior when there is a car EW.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_TrafficContEW */
void TrafficContEW(void *argument)
{
  /* USER CODE BEGIN TrafficContEW */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(90) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{

		if(TL1_Car_Flag || TL3_Car_Flag){ //There is a car EW.
			if(NSTrafficFlag){	//Current traffic light is NS.

				if(TL2_Car_Flag || TL4_Car_Flag){	//If there's a car NS we have to wait.
					vTaskDelay(pdMS_TO_TICKS(redDelayMax));
					if(!PL1_Switch_Flag){ //No overlapping pedestrian crossing
						xSemaphoreTake( FourWayHandle, portMAX_DELAY);
						/*Transition EW to green, NS to red.*/
						pedestrianOffEW();
						pedestrianOffNS();

						trafficTransition();
						trafficOnEW();
						trafficOffNS();

						pedestrianOnEW();
						xSemaphoreGive(FourWayHandle);
					}
				}
				else{	//If there is no car NS, just go.
					if(!PL1_Switch_Flag){ //No overlapping pedestrian crossing
						xSemaphoreTake( FourWayHandle, portMAX_DELAY);
						/*Transition EW to green, NS to red.*/
						pedestrianOffEW();
						pedestrianOffNS();

						trafficTransition();
						trafficOnEW();
						trafficOffNS();

						pedestrianOnEW();
						xSemaphoreGive(FourWayHandle);
					}
				}
			}
			else if(!PL1_Switch_Flag){ //Light is already green and no active pedestrian crossing causing overlap
				osDelay(1);
			}

			else{ //Light is already green, but there is an active pedestrian crossing.
				xSemaphoreTake( FourWayHandle, portMAX_DELAY);
				/*Transition NS to green, EW to red.*/
				pedestrianOffEW();
				pedestrianOffNS();

				trafficTransition();
				trafficOnNS();
				trafficOffEW();
				xSemaphoreGive(FourWayHandle);
			}
		}

		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END TrafficContEW */
}

/* USER CODE BEGIN Header_PedCrossEW */
/**
 * @brief PedCrossNS handles the EW pedestrian crossing events.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_PedCrossEW */
void PedCrossEW(void *argument)
{
  /* USER CODE BEGIN PedCrossEW */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(50) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
		if(PL2_Switch_Flag){ //Button has been pressed.
			if(!EWPedestrianFlag){ //The light is not already green
				while(EWPedTransitioning){ //Wait if the lights are transitioning. It causes trouble otherwise.
					osDelay(1);
				}
				if(!EWPedestrianFlag){ //After the delay the light might have turned green. Check again.
					while(!EWTrafficFlag){//Waits for EW traffic to turn green.
						osDelay(1);
					}
					xSemaphoreTake(FourWayHandle, portMAX_DELAY);
					/*Makes the light green and resets the flag.*/
					pedestrianOnEW();
					pedestrianOffNS();
					PL2_Switch_Flag = 0;

					vTaskDelay(pdMS_TO_TICKS(walkingDelay));
					xSemaphoreGive(FourWayHandle);
				}
			}
			PL2_Switch_Flag = 0; //Resets the flag even if the light wasn't changed.
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END PedCrossEW */
}

/* USER CODE BEGIN Header_NSBlue */
/**
 * @brief NSBlue is responsible for flashing the NS blue light when needed.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_NSBlue */
void NSBlue(void *argument)
{
  /* USER CODE BEGIN NSBlue */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(1000/toggleFreq) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
		if(PL1_Switch_Flag && !NSPedestrianFlag){
			setLeds(P1_Blue);
			vTaskDelay(pdMS_TO_TICKS(1000/toggleFreq)/2);
			resetLeds(P1_Blue);
			vTaskDelay(pdMS_TO_TICKS(1000/toggleFreq)/2);
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END NSBlue */
}

/* USER CODE BEGIN Header_EWBlue */
/**
 * @brief EWBlue is responsible for flashing the EW blue light when needed.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_EWBlue */
void EWBlue(void *argument)
{
  /* USER CODE BEGIN EWBlue */
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(1000/toggleFreq) ; // ms to ticks
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	/* Infinite loop */
	for(;;)
	{
		if(PL2_Switch_Flag && !EWPedestrianFlag){
			setLeds(P2_Blue);
			vTaskDelay(pdMS_TO_TICKS(1000/toggleFreq)/2);
			resetLeds(P2_Blue);
			vTaskDelay(pdMS_TO_TICKS(1000/toggleFreq)/2);
		}
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
	}
  /* USER CODE END EWBlue */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

