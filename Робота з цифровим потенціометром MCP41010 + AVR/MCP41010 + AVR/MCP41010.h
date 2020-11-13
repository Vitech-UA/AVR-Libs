
#ifndef MCP41010_H_
#define MCP41010_H_


#define SPI_PORTX PORTB
#define SPI_DDRX DDRB

#define SPI_MISO 4
#define SPI_MOSI 3
#define SPI_SCK 5
#define SPI_SS 2
#include <avr/io.h>
#include <util/delay.h>


void MCP41010_Init(void);
void MCP41010_WriteValue(unsigned char value); //Функція запису в бітах. Приймає 0..255
void MCP41010_WriteOm(float resistance); //Функція запису в Омах. Приймає 96..8000 Ом.


#endif /* MCP41010_H_ */