#include "main.h"

char dg = 4; // Кількість розрядів в індикаторі.

void SPI_SendByte (char byte)
{
	SPDR = byte;
	while (!(SPSR & (1 << SPIF)));
}
void Send_7219(char rg, char dt)
{
	PORTB &= ~(1<<PORTB2);
	SPI_SendByte(rg);
	SPI_SendByte(dt);
	PORTB |= (1<<PORTB2);
}
void Clear_7219(void)
{
	char i = dg;
	do {
		Send_7219(i, 0xF); //символ пустоты
	} while (--i);
}
void SPI_Init(void)
{
 // ініціалізація портів а вихід
 DDRB |= ((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
 PORTB &= ~((1<<PORTB2)|(1<<PORTB3)|(1<<PORTB5));
 
 // ініціалізація шини SPI
 SPCR |= ((1<<SPE)|(1<<MSTR)|(1<<SPR0));	
}
void MAX7219_Init(void)
{
 Send_7219(0x09, 0xFF);
 Send_7219(0x0B, dg-1);
 Send_7219(0x0A, 0x02); //Яскравість індикатора
 Send_7219(0x0C, 1);    //ввімкнення вимкнення індикатора
 Clear_7219();

}
void Number_7219(volatile long n)
{
	char ng = 0; //переменна¤ дл¤ минуса
	if (n < 0)
	{
		ng = 1;
		n *= -1;
	}
	Clear_7219();
	if (n == 0) {
		Send_7219(0x01, 0); //в первый разр¤д напишем 0
		return;
	}
	char i = 0;
	do {
		Send_7219(++i, n%10);
	    
		n /= 10;
	} while (n);
	if (ng) {
		Send_7219(i+1, 0xA); //символ -
	}
}


main (void)
{
	
    extern	int32_t temperature;
    extern	int32_t    pressure;
	int32_t    altitude = 0;

    char Pres_str[10];
    char Temp_str[10];

	i2c_init();
	SPI_Init();
	BMP180_Calibration();
	MAX7219_Init();

	while (1)
	{

		BMP180_calculation (&temperature, &pressure);
		bmp180CalcAltitude(pressure);
		int pressure1 = pressure/1000;
        int pressure3 = pressure/133.322;    // перевод из Па в мм.рт.ст
		int temp1 = temperature/10;

        Number_7219(pressure3);
		_delay_ms(3000);
		Number_7219(temp1);
		_delay_ms(3000);
		

		
	}
}
