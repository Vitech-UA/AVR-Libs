#include "main.h"

void InitPort(void){
	DDRB |= (1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5);
	PORTB &= ~(0<<PORTB2)|(0<<PORTB3)|(0<<PORTB5);
}

void InitSPI(void){
	SPCR |= (1<<SPE)|(1<<MSTR); //Вмикаємо ШИНУ оголошуємо МК ведучим.

}
void SpiSendByte(char data){
	
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));	PORTB |=(1<<PORTB2);	PORTB &= ~(1<<PORTB2);	
}
int main(void)
{
	char i = 0;
	
	InitPort();
	InitSPI();
	
	
	
	while(1)
	{
	SpiSendByte(i);
	i++;
	if(1>255) i = 0;
	_delay_ms(50);
	
	
	}
}