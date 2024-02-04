#ifndef WRAPPER
#define WRAPPER

#include "main.h"
#include "stm32f3xx_hal.h"



typedef TIM_HandleTypeDef timerTip;
typedef UART_HandleTypeDef UARTTip;

typedef enum
{
	
	BLUE=0,
	RED=1,
	ORANGE=2,
	GREEN=3,
	BLUE2=4,
	RED2=5,
	ORANGE2=6,
	GREEN2=7,
} LED;


void GetHandles(UART_HandleTypeDef *huart1,TIM_HandleTypeDef *htim16);

void UART_Receive(uint8_t *number);

void UART_Transmit(uint8_t *number);

void callfun();

__weak void callbackTim(void);

__weak void callbackR(UART_HandleTypeDef *);

__weak void callbackT(UART_HandleTypeDef *);

void turnOnLED(LED);

void turnOffLED(LED);

uint32_t GetTimerTick(void);

void TimerStart(void);

void Error_Handle(void);

void Init(void);

#endif








