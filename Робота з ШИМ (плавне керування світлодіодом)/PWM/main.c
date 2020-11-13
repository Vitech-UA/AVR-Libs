
#include "main.h"

void port_ini(void){
	PORTB = 0x00;
	DDRB = 0b00001000;
}

int main(void)
{
	int i = 0;
	
	port_ini();
	InitPWM_Timer();
	OCR2 = 1;
	
    while(1)
    {
       for (i=0;i<=250;i++)
       {
		   OCR2++;
		   _delay_ms(100);
       }
	   for (i=0;i<=250;i++)
	   {
		   OCR2--;
		   _delay_ms(100);
	   }
	   
	   
    }
}