#ifndef BATTLESHIP
#define BATTLESHIP

#include "stm32f3xx_hal.h"

typedef enum{
	
	right=0,
	down=1,
	left=2,
	up=3,
	
}rotation;

typedef enum{
	
	carrier=5,
	battleship=4 ,
  destroyer=3, 
  submarine=3, 
	patrol_boat=2,
	
}typeofShip;


typedef struct{
	
	uint8_t orientationX;
	uint8_t orientationY;
	uint8_t rotation;   
	uint8_t typeofShip; 
} Ships;

uint8_t setShip(Ships ship,uint8_t matrix[10][10]);
void initMatrix(uint8_t matrix[10][10]);
void printMatrix(uint8_t matrix[10][10]);

uint8_t encodeShipOrigin(Ships ship);
uint8_t encodeShipsRotation(Ships carrier,Ships battleship, Ships destroyer,Ships submarine, Ships patrol_boat);
uint8_t shoot(uint8_t Px, uint8_t Py,uint8_t matrix[10][10]);


uint8_t decodeBoardMessage(uint8_t message[], uint8_t grid[10][10], CRC_HandleTypeDef* CrcHandle);
void decodeShipOrigin(uint8_t matrix[10][10],uint8_t message[30]);
void encodeMatrixShots(uint8_t matrix[10][10], uint8_t* savePlace);

void encodeBoardMessage(uint8_t* sendMessage, uint8_t matrix[10][10], CRC_HandleTypeDef* CrcHandle);
uint8_t parseMessageInput(uint8_t* message, UART_HandleTypeDef* huart, CRC_HandleTypeDef* hcrc,uint8_t matrix[10][10];);


#endif
