#include "PWM.h"

void InitPWM_Timer(void){

ASSR = 0;	
TCCR2 = 0b01101110;
TCNT2 = 0x00;	
OCR2 = 0x00; // 0% скважности
TIMSK |=0;

}