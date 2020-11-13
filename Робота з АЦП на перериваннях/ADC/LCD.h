
#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define LCD_PORT PORTB
#define DDR_LCD_PORT DDRB

#define E1 LCD_PORT |= 0b00001000; //Установка лінії Е в 1.
#define E0 LCD_PORT &= 0b11110111; //Установка лінії E в 0.
#define RS1 LCD_PORT |= 0b00000100 //Установка лінії RS в 1.
#define RS0 LCD_PORT &= 0b11111011 //Установка лінії RS в 0.

// RS-LCD_PORT PIN 2
// R/W-GND
// E-LCD_PORT3 PIN 3
//
// D4-LCD_PORT PIN 4
// D5-LCD_PORT PIN 5
// D6-LCD_PORT PIN 6
// D7-LCD_PORT PIN 7

void Port_Init(void);

void LCD_Init(void);

void SendHalfByte(unsigned char c);

void SendByte(unsigned char c, unsigned char mode);

void SendChar(unsigned char c);

void LCD_gotoxy(unsigned char x, unsigned char y);

void LCD_Print(char str1[]);

void LCD_Clear(void);




#endif /* LCD_H_ */