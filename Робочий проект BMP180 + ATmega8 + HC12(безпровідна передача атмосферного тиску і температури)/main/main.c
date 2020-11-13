#include "main.h"



int main (void)
{
 extern	int32_t temperature;
 extern	int32_t    pressure;
	int32_t    altitude = 0;

   char Pres_str[10];
   char Temp_str[10];


	// инициализации
	
	i2c_init();
	BMP180_Calibration();
	USART_ini();

	

	while (1)
	{

		BMP180_calculation (&temperature, &pressure);
		bmp180CalcAltitude(pressure);


		int pressure1 = pressure/1000;
		

		int pressure3 = pressure/133.322;    // перевод из Па в мм.рт.ст

		int temp1 = temperature/10;
		

		itoa(pressure3,Pres_str,10);
		usart_putline(Pres_str);
		
		itoa(temp1,Temp_str,10);
		usart_putline(Temp_str);



		_delay_ms(1000);
	}
}
