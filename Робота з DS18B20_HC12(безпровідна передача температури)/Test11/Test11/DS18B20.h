#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

#define NOID 0xCC //Пропустити ідентифікацію
#define T_CONVERT 0x44 // Код заміру температури
#define READ_DATA 0xBE // Передача температури

#define PORT_temp PORTD
#define DDR_temp DDRD
#define PIN_temp PIND
#define BIT_temp 2





int dt_check(void);             //Функція перетворення показів сенсора в температуру
char dt_testdevice(void);       // Функція визначення наявності пристрою на шині.
char dt_readbit();              //Функція читання бiта з пристрою
unsigned char dt_readbyte();    //Функція читання байта з пристрою
char converttemp(unsigned int tt);
void dt_sendbyte(unsigned char bt);
void dt_sendbit(char bt);


#endif /* DS18B20_H_ */