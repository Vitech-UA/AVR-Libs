#include "MCP41010.h"


void MCP41010_Init(void)
{
	// ініціалізація портів на вихід
	DDRB |= ((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
	PORTB |= (1<<PORTB2)|(0<<PORTB3)|(0<<PORTB5);
	
	// ініціалізація шини SPI  SPI mode 0-0
	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

void MCP41010_WriteValue(unsigned char value)
{
	SPI_PORTX &= ~(1<<SPI_SS);
	SPDR = 0b00011001; //Ініціалізація цифрового потенціометра
	while(!(SPSR & (1<<SPIF)));
	SPDR = value;
	while(!(SPSR & (1<<SPIF)));
	SPI_PORTX |= (1<<SPI_SS);
}

MCP41010_WriteOm(float resistance)
{
	unsigned char value;
	
	value = (resistance * 0.028);
	
	SPI_PORTX &= ~(1<<SPI_SS);
	SPDR = 0b00011001; //Ініціалізація цифрового потенціометра
	while(!(SPSR & (1<<SPIF)));
	SPDR = ~value;
	while(!(SPSR & (1<<SPIF)));
	SPI_PORTX |= (1<<SPI_SS);
	
}