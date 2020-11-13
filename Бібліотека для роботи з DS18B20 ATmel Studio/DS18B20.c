#include "DS18B20.h"


// Функція визначення наявності пристрою на шині.
char dt_testdevice(void){
	
	char stektemp = SREG;       // збережемо значення стеку.
	cli();
	char dt;
	DDR_temp |= 1<<BIT_temp;  // Пін на вхід
	_delay_us(485);             // Затримка мінімум 485 мкС.
	DDR_temp &= ~(1<<BIT_temp); // Відпускаємо шину
	_delay_us(65);
	if ((PIN_temp & (1<<BIT_temp))==0) // Перевірка чи відповів пристрій
	{
		dt=1;// Пристрій є
	} 
	else dt=0;// Пристрій відсутній
	
	SREG = stektemp;            // Повертаємо значення стеку.
	_delay_us(420);             // Затримка мінімум 420 мкС.
	return dt;
	
	
		
}

//Функція читання бiта з пристрою
char dt_readbit(){
	char stektemp = SREG;       // збережемо значення стеку.
	cli();
	char bt;                    // змінна зберігання біта
	DDR_temp |= 1<<BIT_temp;  // Пін на вхід
	_delay_us(2);               // Затримка мінімум 2 мкС.
	DDR_temp &= ~(1<<BIT_temp); // Відпускаємо шину
	_delay_us(13);              // Затримка мінімум 2 мкС.
	bt = (PIN_temp & (1<<BIT_temp))>>BIT_temp; //Читаємо біт
	_delay_us(45);
   SREG = stektemp;            // Повертаємо значення стеку.
   return bt;
   
	
	
}

//Функція читання байта з пристрою
unsigned char dt_readbyte(void){
	char c = 0;
	char i;
	for (i=0;i<8;i++)
	c |= dt_readbit() <<i;
	
	return c;
}

//Функція перетворення показів сенсора в температуру
int dt_check(void){
	unsigned char bt;     // змінна для зчитування байту
	unsigned int tt = 0;
	
 if (dt_testdevice()==1)  // якщо пристрій знайдено
 {
	 dt_sendbyte(NOID);   //Пропускаємо ідентифікацію бо у нас лише один сенсор
	 dt_sendbyte(T_CONVERT); //починаємо читати дані про температуру.
	 _delay_ms(750);   // у 12 бітному режимі перетворення займає 750 мС.
	 dt_testdevice();
	 dt_sendbyte(NOID);
	 dt_sendbyte(READ_DATA); //Даємо команду на зчитування температури
	 bt = dt_readbyte();     // Читаємо молодший біт
	 tt = dt_readbyte();     //Читаємо старший біт
	 tt = (tt<<8)|bt;
 }
 return tt;
}

//Функція запису біта
void dt_sendbit(char bt){
	
char stektemp = SREG;       // збережемо значення стеку.
cli();
DDR_temp |= 1<<BIT_temp;  // Пін на вхід
_delay_us(2);	
if(bt)

DDR_temp &= ~(1<<BIT_temp); // Відпускаємо шину
_delay_us(65);
DDR_temp &= ~(1<<BIT_temp); // Відпускаємо шину

SREG = stektemp;
}

//Функція запису байта
void dt_sendbyte(unsigned char bt){
	char i;
	for (i=0;i<8;i++)
	{
		
		if ((bt & (1<<i)) == 1<<i)
		
		dt_sendbit(1);
		
		else
		
		dt_sendbit(0);
	}	
	
}

// Перетворення температури в одиниці
char converttemp(unsigned int tt){
	
	char t = tt>>4; //відсікаємо біти точності
	return t;
	
}