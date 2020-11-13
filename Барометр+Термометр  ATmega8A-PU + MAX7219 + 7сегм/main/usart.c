#include "usart.h"

void USART_ini (){
 	
  /*UBRRH = (unsigned char) (speed>>8);
  UBRRL = (unsigned char) speed;
  UCSRB = (1<<RXEN)|(1<<TXEN); // Вмикаємо прийом та передачу
  UCSRB |=(0<<RXCIE); // Дозвіл переривання
  UCSRA |=(1<<U2X);// Ввімкнення подвоєння частоти
  UCSRC = (1<<URSEL)|(1<<USBS)|(1<<UCSZ1)|(1<<UCSZ0)|(0<<UPM1)|(0<<UPM0); //Звертаємось до UCSRC */
  UBRRH = 0;
  UBRRL = 51; //скорость обмена 9600 бод
  //разр. прерыв при приеме, разр приема, разр передачи.
  UCSRB = (1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
  //обращаемся к регистру UCSRS, размер слова – 8 бит
  UCSRC = (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0)|(1<<UPM0)|(1<<UPM1);
  
  
 

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
