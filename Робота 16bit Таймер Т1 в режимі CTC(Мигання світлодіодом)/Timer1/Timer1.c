#include "main.h"

unsigned char i;

void Timer_Init(void)
{
	TCCR1B |= (1<<WGM12); // устанавливаем режим СТС (сброс по совпадению)
	TIMSK |= (1<<OCIE1A); //устанавливаем бит разрешения прерывания 1ого счетчика по совпадению с OCR1A(H и L)
	
	OCR1AH = 0x08; //записываем в регистр число для сравнения
	OCR1AL = 0x3D;
	
	TCCR1B |= (1<<CS12);//установим делитель.
}

ISR (TIMER1_COMPA_vect)
{
	PORTC = ~PORTC;
}

int main(void)
{
	DDRC=0xFF;
	
	
	Timer_Init();
	sei();
	
    while(1)
    {
        
    }
}