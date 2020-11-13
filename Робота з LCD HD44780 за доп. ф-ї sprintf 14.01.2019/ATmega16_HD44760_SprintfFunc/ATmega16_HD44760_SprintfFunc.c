#include "main.h"

int main(void)
{
	LCD_Init();
	LCD_Clear();
	LCD_gotoxy(0,0);
	
	char LCD_BUFFER[33];
	char sign;
	int i = 245;
	int j = 69;
	
	//sprintf(LCD_BUFFER,"t=%c%i.%u\xdfC",sign,temp/10,temp%10);
	sprintf (LCD_BUFFER, "%s %d %d", "one", i, j);
	
	LCD_Print(LCD_BUFFER);
    while(1)
    {
        
		
		LCD_gotoxy(0,0);
		
		i++;
		j++;
		
		sprintf (LCD_BUFFER, "%s %d %d", "one", i, j);
		LCD_Print(LCD_BUFFER);
		_delay_ms(80);
    }
}