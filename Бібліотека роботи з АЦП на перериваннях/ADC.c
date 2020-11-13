#include "ADC.h"

void ADC_Init(void){
	
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); // Дозвіл використання АЦП + дільник на 128.
	                                                      // 64кГц
	ADMUX |= (1<<REFS1)|(1<<REFS0); // Вмик. вн.Джерело Опорної напруги = 2.56В, вхід ADC0

}

unsigned int ADC_Convert(void){
	
	ADCSRA |= (1<<ADSC); //Запускаємо перетворення
	while((ADCSRA & (1<<ADSC))); // Чекаємо завершення перетворення
	return(unsigned int) ADC;
	
}