#include "LCD.h"



void Port_Init(void)
{
	LCD_PORT = 0x00;
	DDR_LCD_PORT = 0xFF;
	
}
void LCD_Init(void)
{
	Port_Init();
	SendHalfByte(0b00000011);
	_delay_ms(4);
	SendHalfByte(0b00000011);
	_delay_us(100);
	SendHalfByte(0b00000011);
	_delay_ms(1);
	SendHalfByte(0b00000010);
	_delay_ms(1);
	SendByte(0b00101000,0);// Вмикаємо 4-бітний режим (N=1)
	_delay_ms(1);
	SendByte(0b00001100,0);//Вмикаємо зображення (D=1), курсори не вмикаємо
	_delay_ms(1);
	SendByte(0b00000110,0);//Змушуємо курсор рухатись зправа на ліво.
	_delay_ms(1);
	

}
void SendHalfByte(unsigned char c)
{
	c<<=4;
	E1; //Установка лінії Е в 1.
	_delay_us(50);
	LCD_PORT &= 0b00001111; // Зтираємо інформація на шині даних
	LCD_PORT |= c;
	E0; //Установка лінії Е в 0.
	_delay_us(50);
}
void SendByte(unsigned char c, unsigned char mode)
{
	if(mode == 0) RS0;
	else RS1;
	unsigned char hc=0;
	hc = c>>4;
	SendHalfByte(hc);
	SendHalfByte(c);
	
}
void SendChar(unsigned char c)
{
	SendByte(c,1);
}
void LCD_gotoxy(unsigned char x, unsigned char y)
{
	char adress;
	adress = (0x40*y+x)| 0b10000000;
	SendByte(adress,0);
}
void LCD_Print(char str1[])
{
	char n;
	for(n=0; str1[n]!='\0'; n++)
	SendChar(str1[n]);
	
}
void LCD_Clear(void)
{
	SendByte(0b00000001,0);
	_delay_ms(2);
}