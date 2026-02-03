/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "LCD_Test.h"
#include "image.h"
#include "LCD_1in69.h"
#include "DEV_Config.h"
#include "CST816T.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
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

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void LCD_Proc(void *argument);
void TCH_Proc(void *argument);
void led_proc(void *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	xTaskCreate(LCD_Proc,"LCD_Task",512*4,NULL,osPriorityBelowNormal7,NULL);
	xTaskCreate(TCH_Proc,"TCH_Task",128*4,NULL,osPriorityNormal,NULL);
	xTaskCreate(led_proc,"led_Task",128*4,NULL,osPriorityNormal,NULL);
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

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void LCD_Proc(void *argument)
{
	uint16_t color_group[6] = {WHITE,RED,BLUE,GREEN,GRAY,BRRED};
	uint8_t i = 0;
	DEV_Module_Init();
	LCD_1IN69_SetBackLight(1000);
	LCD_1IN69_Init(VERTICAL);
	LCD_1IN69_Clear(WHITE);
	LCD_Fill(30,30,50,50,BLACK);
	osDelay(500);
  for(;;)
  {
		if(++i >= 6)
			i = 0;
		LCD_Fill(0,0,240,280,color_group[i]);
  }
}
void TCH_Proc(void *argument)
{
	uint16_t position_x = 0;
	uint16_t position_y = 0;
	uint8_t ch[16] = {0};
	
	CST816T_Init(); 
	uint8_t id = CST816T_GetChipID();
	int len = sprintf((char*)ch, "id: %X\r\n", id);
	HAL_UART_Transmit(&huart1, ch, len, 10);
	osDelay(2000);
  for(;;)
  {
    if(CST816T_Read_Sensor(&position_x,&position_y)) 
		{
			len = sprintf((char*)ch, "X: %d ,Y: %d\r\n", position_x,position_y);
        HAL_UART_Transmit(&huart1, ch, len, 10);
    }
		osDelay(50);
  }
}

void led_proc(void *argument)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		osDelay(500); // 关键：这会让任务进入阻塞态，释放 CPU 给别人
	}
}
