
#include "main.h"
unsigned char sec, min,hour,day,date,month,year;


int main(void)

{
	I2C_Init();
	USART_ini();
	
	//Встановимо но ми час
	I2C_StartCondition(); 
	USART_Transmit(TWSR);
	I2C_SendByte(0b11010000);//Передаємо адресу та біт запису (0)
	USART_Transmit(TWSR);
	
	I2C_SendByte(0);//Переходимо в регістр з 0x00 адресою
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(0));//сек
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(29));//хв
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(20));//години
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(1));//день
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(23));//Число
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(10));//Місяць
	USART_Transmit(TWSR);
	I2C_SendByte(RTC_Convert_From_BinDec(17));//Рік
	USART_Transmit(TWSR);
	
	I2C_StopCondition();
	
	
    while(1)
    {
	   
       I2C_SendByteAdress(0,0b11010000);
	   _delay_ms(1000);
	   I2C_StartCondition();
	   I2C_SendByte(0b11010001);
	   sec = I2C_ReadByte();
	   min = I2C_ReadByte();
	   hour = I2C_ReadByte();
	   day = I2C_ReadByte();
	   date = I2C_ReadByte();
	  month = I2C_ReadByte();
	   year = I2C_ReadLastByte();
	   I2C_StopCondition();
	   
	   sec = RTC_Convert_FromDec(sec);
	   min = RTC_Convert_FromDec(min);
	   hour = RTC_Convert_FromDec(hour);
	   day = RTC_Convert_FromDec(day);
	   date = RTC_Convert_FromDec(date);
	   month = RTC_Convert_FromDec(month);
	   year = RTC_Convert_FromDec(year);
	   
	 
	  USART_Transmit(date/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(date%10+0x30);//Преобразуем число в код числа
	  USART_Transmit('.');
	  USART_Transmit(month/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(month%10+0x30);//Преобразуем число в код числа
	  USART_Transmit('.');
	  USART_Transmit(year/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(year%10+0x30);//Преобразуем число в код числа
	  USART_Transmit(' ');
	  USART_Transmit('-');
	  USART_Transmit(day+0x30);//Преобразуем число в код числа
	  USART_Transmit('-');
	  USART_Transmit(' ');
	  USART_Transmit(' ');
	  USART_Transmit(hour/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(hour%10+0x30);//Преобразуем число в код числа
	  USART_Transmit(':');
	  USART_Transmit(min/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(min%10+0x30);//Преобразуем число в код числа
	  USART_Transmit(':');
	  USART_Transmit(sec/10+0x30);//Преобразуем число в код числа
	  USART_Transmit(sec%10+0x30);//Преобразуем число в код числа
	  USART_Transmit(0x0d);//переход в начало строки
	  USART_Transmit(0x0a);//перевод каретки
    }
}