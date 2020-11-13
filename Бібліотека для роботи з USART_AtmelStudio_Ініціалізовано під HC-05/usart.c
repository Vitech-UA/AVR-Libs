#include "usart.h"

void USART_ini (){
 	
  DDRD &= ~(1<<0);  //rx на вход
  DDRD |= (1<<1);    //tx на выход
  //разрешаем прием, передачу, прерывание по приёму
  UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE)|(0<<UDRIE);
  //8 бит данных, 1 стоп бит, без контроля четности
  UCSRC = (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
  //Baud Rate: 9600
  UBRRL = 0x33;
  
  
 

  }
void USART_Transmit (unsigned char data){
    
	while(!(UCSRA&(1<<UDRE)));
    UDR=data;
    
   	
}	
void usart_putline(char *buffer)
{
	while (*buffer!=0)
	{
		USART_Transmit(*buffer);
		buffer++;
	}

	// Завершение строки символом возврата каретки, т.е. 0x0D и 0x0A
	USART_Transmit(13);
	USART_Transmit(10);
}
