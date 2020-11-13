#include "main.h"


int main(void)
{
	
	char str[10];
	Port_Init();
	LCD_Init();
	SetCursor(0,0);
	ClearLCD();
    PrintStr("Hello World");
	
    while(1)
    {
     for (int i=0; i<=9999;i++)
     {
		 ClearLCD();
		 itoa(i,str,10);
		 PrintStr(str);
		 _delay_ms(8);
     }
         
    }
}