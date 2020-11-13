#include "PWM.h"

void InitPWM_Timer(void){
DDRB |= (1<<PORTB3);
ASSR = 0;	
TCCR2 = 0b01101001;
TCNT2 = 0x00;	
OCR2 = 0x00; // 0% скважности
TIMSK |=0;

}