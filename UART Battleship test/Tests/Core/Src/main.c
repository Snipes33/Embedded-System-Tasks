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
#include "Battleships.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
CRC_HandleTypeDef hcrc;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
uint8_t first_test=0;
uint8_t second_test=0;
uint8_t third_test=0;
uint8_t matrix[10][10];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CRC_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



uint8_t test1(){

	initMatrix(matrix);
		
	Ships carrier1={5,5,0,carrier};

	uint8_t result=	setShip(carrier1,matrix);
	
	if(result !=1) return 0;
		
	uint8_t i;
	
	for(i=5;i<9;i++){
		
	if(matrix[5][i] != 'o') return 0;

		
	}


	return 1;
}

uint8_t test2(){

	Ships carrier2={13,25,0,carrier};
	uint8_t result=	setShip(carrier2,matrix);
	if(result !=103) return 0;
		
	uint8_t i;
	uint8_t j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(matrix[i][j] != 'o') return 0;
		}
	}
	 return 1;
}

	
	
	
	uint8_t test3(){

	
	Ships carrier3={9,9,0,carrier};

	
	uint8_t result=	setShip(carrier3,matrix);
	
	if(result !=1) return 0;
		
	uint8_t i;
	uint8_t j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++)
	
	{
		
		if(matrix[i][j] != 'o') return 0;
	
		
	}
	 
}
	 return 1;
	}

	
	uint8_t test4(){
		
		uint8_t matrix[10][10];
		uint8_t result;
		uint8_t i;
		uint8_t j;
		
		initMatrix(matrix);
		
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				
				if(matrix[i][j]!='_') return 0;

			}
			
		}
		
		
		return 1;
		
	}
	
	uint8_t Collisiontest()
{
	uint8_t i;
	uint8_t j;
	uint8_t correctMatrix[10][10];
	initMatrix(correctMatrix);
	initMatrix(matrix);
	Ships ship1 = {7,7,3,carrier};
	Ships ship2 = {7,7,2,battleship};	
	setShip(ship1, correctMatrix);
	setShip(ship1,matrix);
	uint8_t error = setShip(ship2,matrix);
	if(error!=104) return 0;
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			if(matrix[i][j] != correctMatrix[i][j]) return 0;
	
	return 1;
}



uint8_t DecodeMessageTest()
{
	uint8_t i;
	uint8_t j;
	initMatrix(matrix);
	uint8_t message[30] = {'A', ':', 0x73, 0x31, 0x00, 0x55, 0x98, 0x11, 0x0F, 0xFC, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t correctMatrix[10][10];		
		
	Ships ship1 = {7,7,3,carrier};	
	Ships ship2 = {6,1,2,battleship};	
	Ships ship3 = {0,0,0,destroyer};	
	Ships ship4 = {5,5,0,submarine};	
	Ships ship5 = {9,9,3,patrol_boat};	
	
	initMatrix(correctMatrix);
	setShip(ship1, correctMatrix);
	setShip(ship2, correctMatrix);
	setShip(ship3, correctMatrix);
	setShip(ship4, correctMatrix);
	setShip(ship5, correctMatrix);
	
	shoot(0,0,correctMatrix);
	shoot(1,0,correctMatrix);
	shoot(2,0,correctMatrix);
	shoot(3,0,correctMatrix);
	shoot(4,0,correctMatrix);
	shoot(5,0,correctMatrix);
	shoot(6,0,correctMatrix);
	shoot(7,0,correctMatrix);
	shoot(8,0,correctMatrix);
	shoot(9,0,correctMatrix);
	
	uint8_t errorCode = decodeBoardMessage(message, matrix, &hcrc);
	for(i=0;i<10;i++)
			for(j=0;j<10;j++)
				if(matrix[i][j] != correctMatrix[i][j]) return 0;	
	return 1;
}


uint8_t TestBoardSetup(){
	
	uint8_t message[30] = {'B', 'R', 'S', ':', carrier, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	uint8_t correctMatrix[10][10];
	uint8_t i;
	uint8_t j;
	Ships ship={2,2,0,carrier};
	setShip(ship,correctMatrix);
	if()
	parseMessageInput(message,&huart1,&hcrc);
	
	
		
	}
		
	
	
	
	
	
	

	


	
	


	
	

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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CRC_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	
	first_test=test1();
	second_test=test2();
	third_test=test3();
	if(first_test){
			
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,GPIO_PIN_SET);
			
		}else{
			
			HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,GPIO_PIN_SET);
		}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  hcrc.Init.DefaultPolynomialUse = DEFAULT_POLYNOMIAL_ENABLE;
  hcrc.Init.DefaultInitValueUse = DEFAULT_INIT_VALUE_ENABLE;
  hcrc.Init.InputDataInversionMode = CRC_INPUTDATA_INVERSION_NONE;
  hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
  hcrc.InputDataFormat = CRC_INPUTDATA_FORMAT_BYTES;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE8 PE11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

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
