#include "main.h"


#define UP_Button PORTB0
#define Down_Button PORTB1
#define On_Button PORTB2
#define Off_Button PORTB3
#define SoundPin PORTB7

#define UP_Pin PINB0
#define Down_Pin PINB1
#define On_Pin PINB2
#define Off_Pin PINB3

static unsigned int Led1_State = 0;
static unsigned int Led2_State = 0;
static unsigned int Led3_State = 0;




void Sound(void)
{
	PORTB &= ~(1<<SoundPin);
	_delay_ms(4);
	PORTB |= (1<<SoundPin);
}
void Led1_Enable(void)
{
	PORTC |=(1<<PORTC0);
	Led1_State = 1;
}
void Led1_Disable(void)
{
	PORTC &= ~(1<<PORTC0);
	Led1_State = 0;
}
void Led2_Enable(void)
{
	PORTC |=(1<<PORTC1);
	Led2_State = 1;
}
void Led2_Disable(void)
{
	PORTC &=~(1<<PORTC1);
	Led2_State = 0;
}
void Led3_Enable(void)
{
	PORTC |=(1<<PORTC2);
	Led3_State = 1;
}
void Led3_Disable(void)
{
	PORTC &=~(1<<PORTC2);
	Led3_State = 0;
}

int main(void)
{
	
	unsigned int MenuState;
	int pwm_val = 0;
	char lcd_buffer[20];
	
	
	DDRB &= ~((1<<UP_Button)|(1<<Down_Button)|(1<<On_Button)|(1<<Off_Button)); //Входи
	PORTB |= (1<<UP_Button)|(1<<Down_Button)|(1<<On_Button)|(1<<Off_Button);   //+5V
	
	DDRB |=(1<<SoundPin);   // вихід
	PORTB |= (1<<SoundPin); // GND
	
	DDRC |=(1<<PORTC0)|(1<<PORTC1)|(1<<PORTC2); //Вихід
	PORTC |=(0<<PORTC0)|(0<<PORTC1)|(0<<PORTC2);
	
	DDRD |=(1<<PORTD7); //Вихід
	PORTD &= ~(1<<PORTD7);
	

	char MENU_10[16] = "LED 1   ";
	char MENU_20[16] = "LED 2   ";
	char MENU_30[16] = "LED 3   ";
	char MENU_40[16] = "PWM1  ";
	char MENU_50[16] = "PWM2  ";
	
	char MENU_10_M[16] = "LED 1<";
	char MENU_20_M[16] = "LED 2<";
	char MENU_30_M[16] = "LED 3<";
	char MENU_40_M[16] = "PWM1 <";
	char MENU_50_M[16] = "PWM2 <";
	
	
	
	char MENU_11[16] = "On     ";
	char MENU_12[16] = "Off    ";
	char MENU_11_M[16] = "On <  ";
	char MENU_12_M[16] = "Off<  ";
	
	
	Port_Init();
	LCD_Init();
	InitPWM_Timer();
	
	
	
	SetCursor(0,0);
	PrintStr(MENU_10_M);
	SetCursor(0,1);
	PrintStr(MENU_20);
	MenuState = 10;
	ClearLCD();
	
	while(1)
	{
		itoa(pwm_val,lcd_buffer,10);
		if(!(PINB&0b00000010))	// Вниз
		_delay_us(100);
		if(!(PINB&0b00000010))
		{
			
			if(MenuState == 10 || MenuState == 20|| MenuState == 30||MenuState==40)
			MenuState +=10;
			ClearLCD();
			if(MenuState == 11 || MenuState == 21||MenuState == 31)
			
				MenuState +=1;
				
			
			
			
		}
		
		
		if(!(PINB&0b00000001))	// Вверх
		_delay_us(100);
		if(!(PINB&0b00000001))
		{
			
			if(MenuState == 20 || MenuState == 30||MenuState==40||MenuState == 50)
			MenuState -=10;
			ClearLCD();
			if(MenuState == 12||MenuState == 22||MenuState == 32)
			MenuState -=1;
			ClearLCD();
		}
		if(!(PINB&0b00000100)) // Ok
		_delay_us(100);
		if(!(PINB&0b00000100))
		
		{
			Sound();
			if(MenuState == 10||MenuState == 20||MenuState == 30||MenuState == 40||MenuState ==50)
			MenuState += 1;
			ClearLCD();
		}
		
		if(!(PINB&0b00001000)) // Esc
		_delay_us(100);
		if(!(PINB&0b00001000))
		{
			
			
			if(MenuState == 11||MenuState == 21||MenuState == 31||MenuState==41)
			MenuState -= 1;
			ClearLCD();
			if(MenuState == 12||MenuState == 22||MenuState == 32)
			MenuState -= 2;
			ClearLCD();
		}
		
		
		switch(MenuState){
			
			case 10:
			SetCursor(0,0);
			PrintStr(MENU_10_M);
			SetCursor(0,1);
			PrintStr(MENU_20);
			break;
			
			case 20:
			SetCursor(0,0);
			PrintStr(MENU_10);
			SetCursor(0,1);
			PrintStr(MENU_20_M);
			break;
			
			case 30:
			SetCursor(0,0);
			PrintStr(MENU_20);
			SetCursor(0,1);
			PrintStr(MENU_30_M);
			break;
			
			case 40:
			SetCursor(0,0);
			PrintStr(MENU_40_M);
			SetCursor(0,1);
			PrintStr(MENU_50);
			break;
			
			case 50:
			SetCursor(0,0);
			PrintStr(MENU_40);
			SetCursor(0,1);
			PrintStr(MENU_50_M);
			break;
			
			case 11:
			_delay_ms(3);
			if(Led1_State==0) //Якщо ЛЕД вже ввімкнено, то переходимо в опцію ВИМК.
			MenuState = 12;
			
			SetCursor(0,0);
			PrintStr(MENU_12_M);
			SetCursor(0,1);
			PrintStr(MENU_11);
			if (!(PINB&0b00000100))
			Led1_Disable();
			break;
			
			case 12:
			_delay_ms(3);
			if(Led1_State==1) //Якщо ЛЕД вже вимкнено, то переходимо в опцію ВМИК.
			MenuState = 11;
			
			
			SetCursor(0,0);
			PrintStr(MENU_12);
			SetCursor(0,1);
			PrintStr(MENU_11_M);
			if (!(PINB&0b00000100))
			Led1_Enable();
			break;
			
			case 21:
			_delay_ms(3);
			if(Led2_State==0) //Якщо ЛЕД вже ввімкнено, то переходимо в опцію ВИМК.
			MenuState = 22;
			SetCursor(0,0);
			PrintStr(MENU_12_M);   // off <
			SetCursor(0,1);
			PrintStr(MENU_11); // on
			if (!(PINB&0b00000100))
			Led2_Disable();
			break;
			
			case 22:
			_delay_ms(3);
			if(Led2_State==1) //Якщо ЛЕД вже ввімкнено, то переходимо в опцію ВИМК.
			MenuState = 21;
			SetCursor(0,0);
			PrintStr(MENU_12);   // off
			SetCursor(0,1);
			PrintStr(MENU_11_M); //on <
			if (!(PINB&0b00000100))
			Led2_Enable();
			
			break;
			
			case 31:
			_delay_ms(3);
			if(Led3_State==0) //Якщо ЛЕД вже ввімкнено, то переходимо в опцію ВИМК.
			MenuState = 32;
			SetCursor(0,0);
			PrintStr(MENU_12_M);  //off <
			SetCursor(0,1);
			PrintStr(MENU_11);    //on
			if (!(PINB&0b00000100))
			Led3_Disable();
			break;
			
			
			case 32:
			_delay_ms(3);
			if(Led3_State==1) //Якщо ЛЕД вже ввімкнено, то переходимо в опцію ВИМК.
			MenuState = 31;
			SetCursor(0,0);
			PrintStr(MENU_12);   //off
			SetCursor(0,1);
			PrintStr(MENU_11_M); //on <
			if (!(PINB&0b00000100))
			Led3_Enable();
			break;
			
			case 41:
			SetCursor(0,0);
			PrintStr("PWM LED3 value");
			SetCursor(7,1);
			PrintStr(lcd_buffer);
			
			if(!(PINB&0b00000001))
			{
				
				pwm_val++;
				if (pwm_val > 25)
				{
				  pwm_val = 25;
				  Sound();	
				}
				
				
			}
			
			if(!(PINB&0b00000010))
			{
				
				pwm_val--;
				
				 if (pwm_val < 0)
				 {
					 pwm_val = 0;
					 Sound();	
				 }
				
			}

			break;
		}
		OCR2 = (pwm_val*10);
		_delay_ms(9);
	}
}