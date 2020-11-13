#include "main.h"


int main(void)
{
	USART_ini();
	
	unsigned int tt = 0;
	char str[10];
    while(1)
    {
		tt = converttemp(dt_check());
	    itoa(tt,str,10);
		
      usart_putline(str);
	  _delay_ms(1000); 
    }
}