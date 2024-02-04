#include "wrapper.h"

TIM_HandleTypeDef *handletim16;
UART_HandleTypeDef *handleuart1;


void GetHandles(UART_HandleTypeDef *huart1,TIM_HandleTypeDef *htim16){
	
	handletim16=htim16;
	handleuart1=huart1;
};




void turnOnLED(LED color)
{
	HAL_GPIO_WritePin(GPIOE, 0x0100U << color, GPIO_PIN_SET);
}

void turnOffLED(LED color)
{
	HAL_GPIO_WritePin(GPIOE, 0x0100U << color, GPIO_PIN_RESET);
}

__weak void callbackR(UART_HandleTypeDef *huart1){}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
			callbackR(huart);
}

__weak void callbackT(UART_HandleTypeDef *huart1){}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
			callbackT(huart);
}

__weak void callbackTim(){}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){
	if(htim== handletim16)
	{
		 callbackTim();
	}
}


void UART_Receive(uint8_t *number){
	
	HAL_UART_Receive_IT(handleuart1,number,sizeof(uint8_t));
}

void UART_Transmit(uint8_t *number){
	
	HAL_UART_Transmit_IT(handleuart1,number,sizeof(uint8_t));
}


void TimerStart(){
	HAL_TIM_Base_Start_IT(handletim16);
}

uint32_t GetTimerTick(){
	return __HAL_TIM_GET_COUNTER(handletim16);
}


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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handle();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handle();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handle();
  }
}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
void TimerInit(timerTip* htim16)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16->Instance = TIM16;
  htim16->Init.Prescaler = 6399;
  htim16->Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16->Init.Period = 199;
  htim16->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16->Init.RepetitionCounter = 0;
  htim16->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(htim16) != HAL_OK)
  {
    Error_Handle();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
void UART1_Init(UARTTip* huart1)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1->Instance = USART1;
  huart1->Init.BaudRate = 115200;
  huart1->Init.WordLength = UART_WORDLENGTH_8B;
  huart1->Init.StopBits = UART_STOPBITS_1;
  huart1->Init.Parity = UART_PARITY_NONE;
  huart1->Init.Mode = UART_MODE_TX_RX;
  huart1->Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1->Init.OverSampling = UART_OVERSAMPLING_16;
  huart1->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(huart1) != HAL_OK)
  {
    Error_Handle();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}



/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE8 PE9 PE10 PE11
                           PE12 PE13 PE14 PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

void Init()
{
	HAL_Init();
}


void Error_Handle(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

void callfun()
{
	SystemClock_Config();
	TimerInit(handletim16);
	UART1_Init(handleuart1);
	MX_GPIO_Init();
}

