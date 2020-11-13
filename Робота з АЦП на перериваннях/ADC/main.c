#include "main.h"

int main(void)
{
	unsigned int ADC_value = 0;
	float n;
	char LCD_Buffer[4];
	ADC_Init();
	LCD_Init();
	LCD_Clear();
	
    while(1)
    {
	  
      ADC_value = ADC_Convert(); 
	  LCD_gotoxy(0,0);
	  SendChar(ADC_value/1000 + 0x30);
	  SendChar((ADC_value%1000)/100 + 0x30);
	  SendChar((ADC_value/100)/ 10 + 0x30);
	  SendChar(ADC_value%10 + 0x30);
	  
	  LCD_gotoxy(8,0);
	  n=(float)ADC_value/400;
	  SendChar((unsigned char)n+0x30);
	  SendChar('.');
	  SendChar(((unsigned char)(n*10))%10 + 0x30);
	  SendChar(((unsigned char)(n*100))%10 + 0x30);
	  
	  _delay_ms(50);
	  
    }
}