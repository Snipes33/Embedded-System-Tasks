#include <stdio.h>
#include "Battleships.h"
#include <string.h>
#include <stdlib.h>
#define _OPEN_SYS_ITOA_EXT
	uint8_t encoder=0;
	uint8_t i;
	uint8_t j;
	uint8_t counter=5;
	uint8_t matrix[10][10];
	Ships previous_ship;


void initMatrix(uint8_t matrix[10][10]){
	
	uint8_t i = 0;
	uint8_t j = 0;
	
	for(i=0; i<10; i++) {
      for(j=0;j<10;j++) {
         matrix[i][j]= '_';
      }
   }
}


void printMatrix(uint8_t matrix[10][10]){
	

	uint8_t i;
	uint8_t j;	
	
	for(j=0; j<10;j++){
				printf(" %d", j);
			}
			printf("\n");
	for(i=0; i<10; i++) {
      for(j=0;j<10;j++) {
				printf("|%c", matrix[i][j]);
				if(j==9) printf("|%d",i);
      }
			printf("\n");
   }
}



uint8_t setShip(Ships a, uint8_t matrix[10][10]){
	
	
	uint8_t previousState[10][10];
	uint8_t i;
	
	switch(a.rotation){
		
		case 0:
		{
			for(i=a.orientationX;i<a.orientationX+a.typeofShip;i++){
				if(i>=10){
					
					matrix=previousState;
					return 103;
				}
				if(matrix[a.orientationY][i]=='o'){
					matrix=previousState;
					return 104;
				}
				matrix[a.orientationY][i]='o';
			}
			break;
		}
		
		case 1:
		{
			for(i=a.orientationY;i<a.orientationY+a.typeofShip;i++){
				
					if(i>=10){
					
					matrix=previousState;
					return 103;
				}
				if(matrix[i][a.orientationX]=='o'){
					matrix=previousState;
					return 104;
				}
				matrix[i][a.orientationX]='o';
		}
			break;
			
		}
		
				case 2:
		{
			if(a.orientationY<a.typeofShip-1)return 103;
			for(i=a.orientationX;i>a.orientationX-a.typeofShip;i--){
				
					
				if(matrix[i][a.orientationY]=='o'){
					matrix=previousState;
					return 104;
				}
				matrix[a.orientationY][i]='o';
		}
			break;
			
		}
		
		
				case 3:
		{
			if(a.orientationY<a.typeofShip-1) return 103;
			for(i=a.orientationY;i>a.orientationY-a.typeofShip;i--){
				
				
				if(matrix[i][a.orientationY]=='o'){
					matrix=previousState;
					return 104;
				}
				matrix[i][a.orientationX]='o';
		}
			break;
			
		}
		
		
	}
		
	return 1;	
}

uint8_t encodeShipOrigin(Ships ship)
{
	uint8_t location = ship.orientationX;																									
	if(ship.rotation == 2) location=location-ship.typeofShip+1;														
	location=location<<4;																																	
	location=location+ship.orientationY;																									
	if(ship.rotation == 3) location=location-ship.typeofShip+1;
	
	return location;
	
}

uint8_t encodeShipsRotation(Ships carrier,Ships battleship, Ships destroyer,Ships submarine, Ships patrol_boat){
	
	uint8_t rotation = (carrier.rotation%2);
	rotation = rotation<<1;
	rotation = rotation + (battleship.rotation%2);
	rotation = rotation<<1;
	rotation = rotation + (destroyer.rotation%2);
	rotation = rotation<<1;
	rotation = rotation + (submarine.rotation%2);
	rotation = rotation<<1;
	rotation = rotation + (patrol_boat.rotation%2);
	return rotation;
}

void decodeShipOrigin(uint8_t matrix[10][10], uint8_t message[30]){
	Ships ships[5];
	uint8_t i=0;
	ships[0].typeofShip=carrier;
	ships[1].typeofShip=battleship;
	ships[2].typeofShip=destroyer;
	ships[3].typeofShip=submarine;
	ships[4].typeofShip=patrol_boat;
	uint8_t orientationOffset=0x10;
	for(i=0; i<5;i++){
		
		ships[i].orientationX=(message[i+2] & 0xf0) >>4;
		ships[i].orientationY=(message[i+2] & 0x0f) >>4;
		if((message[7] & orientationOffset)==orientationOffset){
			
			ships[i].rotation=1;
			
		}else{
			
			ships[i].rotation=0;
			
			
		}
		orientationOffset=orientationOffset>>1;
		setShip(ships[i],matrix);
		
		
		
	}
}
	
uint8_t shoot(uint8_t Px, uint8_t Py,uint8_t matrix[10][10]){
	



	if(Px>9||Py>9) return 104;
	
	if(matrix[Py][Px]=='_'){
		matrix[Py][Px]='+';
		return 1;
	}
	else if(matrix[Py][Px]=='o'){
		matrix[Py][Px]='x';
		return 2;
	}
	return 103;
	
	
}


void decodeShots(uint8_t* message, uint8_t matrix[10][10]){
		uint8_t j;
		uint8_t i;
    uint8_t decoder = *message;
	  uint8_t counter = 4;
		decoder = decoder<<4;
    message++;
	
	
	
	
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (counter == 0) {
                decoder = *message;
                message++;
            }
            
            if (decoder & 0x80)  {
							if(matrix[i][j] == 'o') 
							    {
								matrix[i][j] = 'x';
							}
							else
							{
								matrix[i][j] = '+';
							  }
            
						} 
            
           decoder = decoder << 1;
           counter = (counter + 1) % 8;
           }
        }
}



uint8_t decodeBoardMessage(uint8_t* message, uint8_t matrix[10][10], CRC_HandleTypeDef* CrcHandle)
{
	


	decodeShots(message, matrix);
	decodeShots(&message[8], matrix);
	
	uint32_t crc = HAL_CRC_Calculate(CrcHandle, (uint32_t*) message, 26);
	if(crc != *((uint32_t*)(&message[96]))) return 102;
	return 1;
}



void encodeMatrixShots(uint8_t matrix[10][10], uint8_t* savePlace)
{
	uint8_t encoder = 0;
	uint8_t counter = 0;
	uint8_t i;
	uint8_t j;
	for(i=0; i<10; i++)
	{
		for(j=0;j<10; j++)
		{
			if(matrix[i][j] == 'x' || matrix[i][j] == '+')
			{
				encoder=encoder+1;
			}

			 if(i==0 && j==3) counter = 8;
			
			if(counter == 8)
			{
				*savePlace = encoder;
				encoder=0;
				savePlace++;
				counter=0;
			}
			counter++;
			encoder=encoder<<1;
		}
	}
}


uint8_t* parseMessage(uint8_t* message, uint8_t matrix[10][10], UART_HandleTypeDef* huart, CRC_HandleTypeDef hcrc){

	uint8_t sendMessage[30] = {0};
	switch(message[0])
	{
		case 'G':
		{
			uint8_t shooting = shoot(message[2], message[3], matrix);
			if(shooting == 2 || shooting == 3)
			{
				sendMessage[0] = 'K';
				sendMessage[1] = ':';
				sendMessage[2] = 'G';
				
				HAL_UART_Transmit_IT(huart, sendMessage, 30);
				
				encodeBoardMessage(sendMessage, matrix, &hcrc);
				
				HAL_UART_Transmit_IT(huart, sendMessage, 30);

			}

			break;
		}
		case 'A':
		{
			break;
		}
		case 'B':
		{
			break;
		}
		case 'R':
		{
			break;
		}
		case 'E':
		{
			break;
		}
		case 'W':
		{
			break;
		}
		case 'V':
		{
			break;
		}
		case 'K':
		{
			break;
		}
		case 'P':
		{
			break;
		}
		default:
		{
			break;
		}
		
	}
}

uint8_t parseMessageInput(uint8_t* message, UART_HandleTypeDef* huart, CRC_HandleTypeDef* hcrc,uint8_t matrix[10][10]){
	

	Ships ship;
	char strmessage1[]="BRS";
	char strmessage2[]="RDY";
	char strmessage3[]="PGS";
	char strmessage4[]="UPD";
	char strmessage5[]="ECH";
	char str2[4];
	
	str2[0]=message[0];
	str2[1]=message[1];
	str2[2]=message[2];
	str2[3]='\0';
	
	if(strcmp(strmessage1,str2)==0){
		
		char type=message[5];
		
		if(type=='C'){
		ship.typeofShip=carrier;
		
	}
		if(type=='B'){
		ship.typeofShip=battleship;
		
	}
		if(type=='D'){
		ship.typeofShip=destroyer;
		
	}
		if(type=='S'){
		ship.typeofShip=submarine;
		
	}
		if(type=='P'){
		ship.typeofShip=patrol_boat;
		
	}
	
	
	char orientationXfirstvalue[2]={message[6],0};
	char orientationYfirstvalue[2]={message[8],0};
	char rotationFirstValue[2]={message[10],0};

	char* pointer=&orientationXfirstvalue[0];
	char* pointer2=&orientationYfirstvalue[0];
	char* pointer3=&rotationFirstValue[0];
	
	ship.orientationX=atoi(pointer);
	ship.orientationY=atoi(pointer2);
	ship.rotation=atoi(pointer3);
	
	if(previous_ship.typeofShip==ship.typeofShip){
			
		uint8_t i;
		uint8_t j;
		uint8_t previousState[10][10];
		
		
		switch(previous_ship.rotation){
		
		case 0:
		{
			for(i=previous_ship.orientationX;i<previous_ship.orientationX+previous_ship.typeofShip;i++){
				if(i>=10){
					
				
					return 103;
				}
				if(matrix[previous_ship.orientationY][i]=='o'){
					matrix[previous_ship.orientationY][i]='_';
		
				}
				matrix[previous_ship.orientationY][i]='_';
			}
			break;
		}
		
		case 1:
		{
			for(i=previous_ship.orientationY;i<previous_ship.orientationY+previous_ship.typeofShip;i++){
				
					if(i>=10){
					
					
					return 103;
				}
				if(matrix[i][previous_ship.orientationX]=='o'){
					matrix[i][previous_ship.orientationX]='_';

				}
				matrix[i][previous_ship.orientationX]='_';
		}
			break;
			
		}
		
		case 2:
		{
			if(previous_ship.orientationY<previous_ship.typeofShip-1)return 103;
			for(i=previous_ship.orientationX;i>previous_ship.orientationX-previous_ship.typeofShip;i--){
				
					
				if(matrix[i][previous_ship.orientationY]=='o'){
					matrix[i][previous_ship.orientationY]='_';
					
				}
				matrix[previous_ship.orientationY][i]='_';
		}
			break;
			
		}
		
		
		 case 3:
		{
			if(previous_ship.orientationY<previous_ship.typeofShip-1) return 103;
			for(i=previous_ship.orientationY;i>previous_ship.orientationY-previous_ship.typeofShip;i--){
				
				
				if(matrix[i][previous_ship.orientationY]=='o'){
					matrix[i][previous_ship.orientationY]='_';
				
				}
				matrix[i][previous_ship.orientationX]='_';
		}
			break;
			
		}
		
		
	}
		
	return 1;	
}
	
		previous_ship.typeofShip=ship.typeofShip;
		previous_ship.orientationX=ship.orientationX;
		previous_ship.orientationY=ship.orientationY;
		previous_ship.rotation=ship.rotation;
		
		setShip(ship,matrix);
		
		
 }
	
	if(strcmp(strmessage2,str2)==0){
		uint8_t sendingmessage[]="Ready";
		HAL_UART_Transmit_IT(huart,sendingmessage,30);

}
	
	if(strcmp(strmessage3,str2)==0){
		
		char PX=message[4];
		char* pointer=&PX;
		uint8_t Px=atoi(pointer);
		
		char PY=message[6];
		char* pointer2=&PY;
		uint8_t Py=atoi(pointer2);
		
		if(Px>9 || Py>9) return 104;
		
}
	
	
	if(strcmp(strmessage4,str2)==0){
		printMatrix(matrix);
		
		
}

	
	if(strcmp(strmessage5,str2)==0){
		uint8_t i;
		uint8_t j;
		uint8_t sendingMessage[30];
		sendingMessage[0]='E';
		sendingMessage[1]='C';
		sendingMessage[2]='H';
		sendingMessage[3]=':';
		
		for(i=4;i<26;i++){
			for(j=4;j<26;j++){
		sendingMessage[i]=message[j];
		  }
	  }

		*((uint32_t*)(&sendingMessage[26])) = HAL_CRC_Calculate(hcrc,(uint32_t*)sendingMessage,26);
		HAL_UART_Transmit_IT(huart,sendingMessage,30);
		}
	
		
}






void encodeBoardMessage(uint8_t* sendMessage, uint8_t matrix[10][10], CRC_HandleTypeDef* CrcHandle)
{
				Ships carrier;
				Ships battleship;
				Ships destroyer;
				Ships submarine;
				Ships patrol_boat;
	
	
			  sendMessage[0] = 'A';
				sendMessage[1] = ':';
	
				sendMessage[2] = encodeShipOrigin(carrier);
				sendMessage[3] = encodeShipOrigin(battleship);
				sendMessage[4] = encodeShipOrigin(destroyer);
				sendMessage[5] = encodeShipOrigin(submarine);
				sendMessage[6] = encodeShipOrigin(patrol_boat);
				sendMessage[7] = encodeShipsRotation(carrier, battleship, destroyer, submarine, patrol_boat);
	
				encodeMatrixShots(matrix, &sendMessage[8]);
	
				*((uint32_t*)(&sendMessage[96])) = HAL_CRC_Calculate(CrcHandle,(uint32_t*)sendMessage,26);
}

