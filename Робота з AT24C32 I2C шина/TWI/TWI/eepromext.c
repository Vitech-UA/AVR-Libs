#include "eepromext.h"
char err1 = 0; // сюди повертається помилка

//Функція запису байту в мікросхему AT24Cxx
int EepromWriteByte(unsigned char c)
{
	TWDR=c;//запишем байт в регистр данных
	TWCR = (1<<TWINT)|(1<<TWEN);//включим передачу данных
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MT_DATA_ASK)
	{
		return 1;
	}
	return 0;
}



//Функція читання байту з мікросхеми AT24Cxx
unsigned char EepromReadByte(void)
{
	err1=0;
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);//включим прием данных
	while(!(TWCR & (1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MR_DATA_ASK) err1=1;
	else err1=0;
	return TWDR;
}


//Функція читання останнього байту з мікросхеми AT24Cxx
unsigned char EepromReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);//включим прийом даних
	while(!(TWCR&(1<<TWINT)));//подождем пока установится TWIN
	if ((TWSR & 0xF8) != TW_MR_DATA_NASK) err1=1;
	else err1=0;
	return TWDR;
	
}