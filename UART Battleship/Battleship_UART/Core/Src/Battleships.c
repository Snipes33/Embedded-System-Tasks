#include <stdio.h>
#include "Battleships.h"
	uint8_t encoder=0;
	uint8_t i;
	uint8_t j;
	uint8_t counter=5;


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

uint8_t decodeShipOrigin(uint8_t matrix[10][10], uint8_t message[30], CRC_HandleTypeDef* HandleCrc){
	Ships ships[5];
	uint8_t i=0;
	ships[0].typeofShip=carrier;
	ships[1].typeofShip=battleship;
	ships[2].typeofShip=destroyer;
	ships[3].typeofShip=submarine;
	ships[4].typeofShip=patrol_boat;
	uint8_t orientationOffset=16;
	uint32_t crc= HAL_CRC_Calculate(HandleCrc,(uint32_t*) message,26);
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

void bitMap(uint8_t matrix[10][10],uint8_t *pointer){
	

	
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(matrix[i][j]=='x'||matrix[i][j]=='+'){
				
				encoder=encoder+1;
				
			}
			
				
			if(counter==8){
				*pointer=encoder;
				encoder=0;
				pointer++;
				counter=0;
				
			}
		counter++;
			
		encoder=encoder<<1;
		}
	}
}

void bitMapdecoder(uint8_t *pointer, uint8_t matrix[10][10]){
	
	
	
	
	uint8_t i;
	uint8_t j;
	uint8_t counter=4;
	uint8_t flag=0;
	uint8_t decoder=*pointer;
	decoder=decoder<<4;
	pointer++;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(counter==0){
				decoder =*pointer;
				pointer++;
				
			}
			if(decoder & 0x80){
				if(matrix[i][j]=='o'){
					matrix[i][j]='x';
					
				}else{
					
					matrix[i][j]='+';
				}
			}
			decoder=decoder<<1;
			counter=(counter+1)%8;
		}
	}
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

uint8_t* parseMessage(uint8_t* message, uint8_t matrix[10][10], UART_HandleTypeDef* huart, CRC_HandleTypeDef hcrc)
{
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




void encodeBoardMessage(uint8_t* sendMessage, uint8_t matrix[10][10], CRC_HandleTypeDef* CrcHandle)
{
				sendMessage[0] = 'A';
				sendMessage[1] = ':';
				sendMessage[2] = encodeShipOrigin(carrier);
				sendMessage[3] = encodeShipOrigin(battleship);
				sendMessage[4] = encodeShipOrigin(destroyer);
				sendMessage[5] = encodeShipOrigin(submarine);
				sendMessage[6] = encodeShipOrigin(patrolBoat);
				sendMessage[7] = encodeShipsRotation(carrier, battleship, destroyer, submarine, patrol_boat);
				encodeShots(matrix, &sendMessage[8]);
				*((uint32_t*)(&sendMessage[96])) = HAL_CRC_Calculate(CrcHandle,(uint32_t*)sendMessage,26);
}









void encodeShots(uint8_t matrix[10][10], uint8_t* savePlace)
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
				encoder=encoder + 1;
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
