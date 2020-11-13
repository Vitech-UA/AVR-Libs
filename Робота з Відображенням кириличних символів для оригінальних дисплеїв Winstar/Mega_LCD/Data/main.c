/*
 * Mega_LCD.c
 *
 *  Created: 12.01.2014 16:27:33
 *  Библиотека с поддержкой русских символов.
 */ 

#include "define.h"
#include "lcd.h"
#include "init.h"
#include <avr/pgmspace.h>
#include <util/delay.h>	

uint8_t *pBuf;//определяем переменную указатель на буфер
uint8_t count; 
uint8_t text_1[]="Привет";	
	 				
int main(void)
{
	init();//Инициализация МК и остальной обвязки.
	pBuf=BCD_GetPointerBuf();//инициализация переменной pBuf 
							 //для вывода данных на LCD.
    while(1)
	{
		BCD_3(count);
		LCDstring_of_sramXY(pBuf,0,1);
		count++;
		LCDstring_of_sramXY(text_1,0,0);
		
		_delay_ms(200);
	}
}




	