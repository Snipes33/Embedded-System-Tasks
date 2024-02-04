/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
	
	#include <stdlib.h>
	#include "wrapper.h"
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
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t number=0;
uint8_t flag=0;
uint8_t flagTime=0;
uint32_t lastTime=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */


void callbackR(UART_HandleTypeDef *hspi1)
{
	 
	flag=1;
	flagTime=0;
	number++;
	//HAL_UART_Transmit_IT(hspi1,&number,sizeof(uint8_t));
	

	//UART_Transmit(&number);

}

void callbackT(UART_HandleTypeDef *huart1){

	flag = 0;
	if((number & 1) == 1) turnOnLED(BLUE); else turnOffLED(BLUE);
	if((number & 2) == 2) turnOnLED(RED); else turnOffLED(RED);
	if((number & 4) == 4) turnOnLED(ORANGE); else turnOffLED(ORANGE);
	if((number & 8) == 8) turnOnLED(GREEN); else turnOffLED(GREEN);
	if((number & 16) == 16) turnOnLED(BLUE2); else turnOffLED(BLUE2);
	if((number & 32) == 32) turnOnLED(RED2); else turnOffLED(RED2);
	if((number & 64) == 64) turnOnLED(ORANGE2); else turnOffLED(ORANGE2);
	if((number & 128) == 128) turnOnLED(GREEN2); else turnOffLED(GREEN2);
	UART_Receive(&number);

}

void  callbackTim(){
	flagTime=1;
	
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
		GetHandles(&huart1,&htim16);
		TimerStart();
		UART_Receive(&number); 
  while (1)
  {
		if (flag && flagTime)
		{
			UART_Transmit(&number);
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
