
#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define E1 PORTD |= 0b00001000; //Установка лінії Е в 1.
#define E0 PORTD &= 0b11110111; //Установка лінії E в 0.
#define RS1 PORTD |= 0b00000100 //Установка лінії RS в 1.
#define RS0 PORTD &= 0b11111011 //Установка лінії RS в 0.

void Port_Init(void);

void LCD_Init(void);

void SendHalfByte(unsigned char c);

void SendByte(unsigned char c, unsigned char mode);

void SendChar(unsigned char c);

void SetCursor(unsigned char x, unsigned char y);

void PrintStr(char str1[]);

void ClearLCD(void);




#endif /* LCD_H_ */