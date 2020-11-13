#include "TWI.h"

void I2C_Init(){
	TWBR = 0x20; // Швидкість передачі (При 8 Мгц камня на шині буде 100 кГц)
}

void I2C_StartCondition(void){
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2C_StopCondition(void){
	
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void I2C_SendByte(unsigned char c){
	TWDR = c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу байта
	while (!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
}

void I2C_SendByteAdress(unsigned char c, unsigned char addr){
	
	 I2C_StartCondition(); // Отправим условие START
	 I2C_SendByte(addr); // Отправим в шину адрес устройства + бит чтения-записи
	 I2C_SendByte(c);// Отправим байт данных
	 I2C_StopCondition();// Отправим условие STOP
}

unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}

unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}