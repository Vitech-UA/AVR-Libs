/*
 * Mega_LCD.c
 *
 *  Created: 12.01.2014 16:27:33
 *  ���������� � ���������� ������� ��������.
 */ 

#include "define.h"
#include "lcd.h"
#include "init.h"
#include <avr/pgmspace.h>
#include <util/delay.h>	

uint8_t *pBuf;//���������� ���������� ��������� �� �����
uint8_t count; 
uint8_t text_1[]="������";	
	 				
int main(void)
{
	init();//������������� �� � ��������� �������.
	pBuf=BCD_GetPointerBuf();//������������� ���������� pBuf 
							 //��� ������ ������ �� LCD.
    while(1)
	{
		BCD_3(count);
		LCDstring_of_sramXY(pBuf,0,1);
		count++;
		LCDstring_of_sramXY(text_1,0,0);
		
		_delay_ms(200);
	}
}




	