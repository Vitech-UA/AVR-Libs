
 
#include "define.h"  
#include "LCD.h"   
#include <util/delay.h>
#include <avr/pgmspace.h>

#ifndef F_CPU
#error "F_CPU not defined"
#endif

static void LCDcommand(uint8_t);
static void Send_byte(uint8_t);
static void Busy_flag(void);
static void HiPin(void);
static void OutPin(void);
static void InPin(void);
static void Strob(void);
static uint8_t lcd_rus(uint8_t);

//������� ������������� � ������� �������.
static const unsigned char PROGMEM convert_HD44780[64] =
{
	0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,
	0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,
	0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,
	0xAC,0xE2,0xAD,0xAE,0xAD,0xAF,0xB0,0xB1,
	0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,
	0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,
	0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,
	0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7
};

//���������������� ������� ��� LCD, ��� ���������� � ���������.
#if 1
void LCDdata(uint8_t i)						//�������� ������� ��� ����������� �� �������.
{
	Busy_flag();	//�������� ������ ���� ���������, � �������� �� �������?
	CPORT|=(1<<RS); //RS=1 �������� ������ � LCD
	Send_byte(lcd_rus(i));
	CPORT&=~(1<<RS);//RS=0
}
void LCDdataXY (uint8_t a, uint8_t b,uint8_t c)	//������� 1 ������ �� ������� � X, Y ������� .
{
	LCDGotoXY(b,c);
	LCDdata(a);
}
void LCDGotoXY(uint8_t x,uint8_t y)			//������������� ������ � X, Y �������
{
	 uint8_t Address;
	
	switch(y)
	{
		case 0: Address = LINE0+x; 
				break;
		case 1: Address = LINE1+x; 
				break;
		default: Address = LINE0+x;
	}
	
	LCDcommand(1<<7 | Address);
}
void LCDstringXY(char *i,uint8_t x,uint8_t y) //������� ������ �� ������� X,Y
{
	LCDGotoXY(x,y);
	while( *i )
	{
		LCDdata(*i++ );
	}
}
void LCDsendString(char *s)//������� ������ �� �������.
{
	while( *s )
	{
		LCDdata(*s++ );
	}
	
}
void LCDstring_of_sramXY(uint8_t* data,uint8_t x, uint8_t y)
{
	LCDGotoXY(x,y);
	if (!data)
	{
		return;
	}
	
	uint8_t i=0;
	while(data[i] != '\0')
	{
		LCDdata(data[i]);
		i++;
	}
}
void LCDstring_of_flashXY(const uint8_t *FlashLoc,uint8_t x,uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	for(i=0;(uint8_t)pgm_read_byte(&FlashLoc[i]);i++)
	{
		LCDdata((uint8_t)pgm_read_byte(&FlashLoc[i]));
	}
}
void LCDinit(void)							//�������������� �������
{
	//����� �������������� LCD, ���� � init �������� � 100 ���� �������, ���� ������� ������������. 
	_delay_ms(100);
	CDDR |=  (1<<RS)|(1<<E)|(1<<RW);   //��������� ������ 
	CPORT&=~((1<<RS)|(1<<E)|(1<<RW));  //��������� ������ 
	OutPin();						   //��������� ������
	
	uint8_t i=0;
	while (i!=3)
	{
		#ifdef  LCD_8BIT       //�������� ������� 0x30.
		        DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4)|(0<<DB3)|(0<<DB2)|(0<<DB1)|(0<<DB0);
		#else
				DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(1<<DB4);
		#endif
		
		Strob();
		_delay_ms(5);
		i++;
	}
	
	//����������� ���� ��������, ����� ��������� � �������� �����������.
	
	#ifdef  LCD_8BIT
			LCDcommand(0b00111000);//8�� ������ ���������, ��� ������, 5x8 �����.
	#else   //������ ��� ���������� ������ ��� ������� �������
			Busy_flag();
			OutPin();
			DPORT|=(0<<DB7)|(0<<DB6)|(1<<DB5)|(0<<DB4);//4� ������ ��������� 
			Strob();
			LCDcommand(0b00101000);//��� ������, 5x8 �����.
	#endif
	
	LCDcommand(0b1100);  //�������� ������� + ��� ����������� ��������.
	LCDcommand(0b110);   //������� ������ ������ ����� ��������� �� n+1
	LCDcommand(0b10);    //������ � ������� 0,0 + ����� ���� �������
	LCDcommand(0b1);     //������� ������� 
	//�������� ���������� ���������. ��������� � ����������.
}
void LCDblank(void)			//������� ��������� ���� �� �������
{
	LCDcommand(0b1000);
}
void LCDnblank(void)		//������� ������� ���� �� ������� + ��������� ������� �������.
{
	LCDcommand(0b1100);
}
void LCDclear(void)			//������� ������� + ������ �� ������� 0,0
{
	LCDcommand(0b1);
}
void LCDcursor_bl(void)		//�������� �������� ������
{
	LCDcommand(0b1101);
}
void LCDcursor_on(void)		//�������� �������������� ������
{
	LCDcommand(0b1110);
}
void LCDcursor_vi(void)		//�������� ��� �������
{
	LCDcommand(0b1111);
}
void LCDcursorOFF(void)		//��������� ������
{
	LCDcommand(0b1100);
}
void LCDacr(void)			//C������ ������ ������ ����� ��������� �� n+1
{
	LCDcommand(0b110);
}
void LCDacl(void)			//C������ ������ ������ ����� ��������� �� n-1
{
	LCDcommand(0b100);
}
void LCDcursorl(void)		//�������� ������ ����� �� 1
{
	LCDcommand(0b10000);
}
void LCDcursorr(void)		//�������� ������ ������ �� 1
{
	LCDcommand(0b10100);
}
void LCDcursorln(uint8_t n)	//�������� ������ ����� �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10000);
	}
}
void LCDcursorrn(uint8_t n)	//�������� ������ ������ �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b10100);
	}
}
void LCDscreenl(void)		//�������� ����� ����� �� 1
{
	LCDcommand(0b11000);
}
void LCDscreenr(void)		//�������� ����� ������ �� 1
{
	LCDcommand(0b11100);
}
void LCDscreenln(uint8_t n)	//�������� ����� ����� �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11000);
	}
}
void LCDscreenrn(uint8_t n)	//�������� ����� ������ �� n ��������
{
	for (uint8_t i=0;i<n;i++)
	{
		LCDcommand(0b11100);
	}
}
void LCDscreenL(void)		//� ������ ����� �������� ����� ����� ��������� �����
{
	LCDcommand(0b101);
}
void LCDscreenR(void)		//� ������ ����� �������� ����� ����� ��������� ������
{
	LCDcommand(0b111);
}
void LCDresshift(void)      //���������� ������ � ������� 0,0 + ����� ���� �������, ����������� ��������
{
	LCDcommand(0b10);
}

//��������� �������, �� �� �������, ��� ��� ������ �������.
static void LCDcommand(uint8_t i)	//�������� �������, ��������� �������.
{
	Busy_flag();	//�������� ������ ���� ���������, � �������� �� �������?
	Send_byte(i);
}
static void Send_byte(uint8_t i)	//�������� ������ LCD, ���������� ��������� Send_command � Send_data.
{
	OutPin();
	
	#ifdef  LCD_8BIT
			if ((i&1)==1)
			{
				DPORT|=(1<<DB0);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB1);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB2);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB3);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			i=i>>1;
			
			if ((i&1)==1)
			{
				DPORT|=(1<<DB7);
			}
			
		    Strob();
			
	#else
			
			uint8_t higb = ((i&0b11110000)>>4);
			uint8_t lowb =  (i&0b00001111);
	
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			higb=higb>>1;
			if ((higb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
			OutPin();
	
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB4);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB5);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB6);
			}
			lowb=lowb>>1;
			if ((lowb&1)==1)
			{
				DPORT|=(1<<DB7);
			}
	
			Strob();
	#endif
	
	HiPin();
}
static void Busy_flag(void)		    //�������� ����� ���������
{
	InPin();
	CPORT|=(1<<RW);	  //R/W=1 ������ �� LCD
	
	#ifdef  LCD_8BIT
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//�������� �����.
				asm("nop");
				asm("nop");
				
				if (!(DPIN&(1<<DB7)))//������� � ��������� ���� ���������.
				{
					i=0;
				}
				
				CPORT&=~(1<<E);//��������� �����.
				asm("nop");
				asm("nop");						
			}
	#else
			uint8_t i=1;
			while(i==1)
			{
				CPORT|=(1<<E);//�������� �����.
				asm("nop");
				asm("nop");
		
				if (!(DPIN&(1<<DB7)))//������� � ��������� ���� ���������.
				{
					i=0;
				}
		
				CPORT&=~(1<<E);//��������� �����.
				asm("nop");
				asm("nop");
				Strob();
				asm("nop");
				asm("nop");
		
			}
	#endif
	
	CPORT&=~(1<<RW);   //R/W=0 
}
static void HiPin(void)			    //��������� ���� � ��������� Hi.
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
    #endif
}
static void OutPin(void)			//��������� ���� � ��������� "�����".
{
	#ifdef  LCD_8BIT
			DDDR =0xFF;
			DPORT=0;
	#else
			DDDR |=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
			DPORT&=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
	#endif
}
static void InPin(void)			    //��������� ���� � ��������� "����".
{
	#ifdef  LCD_8BIT
			DDDR =0;
			DPORT=0xFF;
	#else
			DDDR &=~((1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4));
			DPORT|=  (1<<DB7)|(1<<DB6)|(1<<DB5)|(1<<DB4);
	#endif
}
static void Strob(void)             //���/���� ������ �
{
	CPORT|=(1<<E);//�������� �����.
	_delay_us(1);
	CPORT&=~(1<<E);//��������� �����.
}
static uint8_t lcd_rus(uint8_t c)
{

	if  (c > 191)
	{
		c -=192;
		c= pgm_read_byte(&convert_HD44780[c]);
	}

	return c;
}
/*
static void LCDset(void)			//������������ ������� 5x8 �����
{
	LCDcommand(0b101000);
}*/
/*
void LCDstring_of_sram(uint8_t* data,uint8_t nBytes,uint8_t x, uint8_t y)
{
	uint8_t i;
	LCDGotoXY(x,y);
	if (!data) 
	{
		return;
	}
	
	for(i=0; i<nBytes; i++)
	{
		LCDdata(data[i]);
	}
	
	
}*/
#endif

/*���������� ��� �������� �������� ����� � ������� � ������ �� �� ���*/
#if 1
#ifdef BCD_SYM
#define BCD_SYMBOL  48

#ifdef MIRROR_NULL
#define SYMB_NULL 48
#else
#define SYMB_NULL 32
#endif
#else
#define BCD_SYMBOL  0
#define SYMB_NULL   0
#endif

#ifdef BCD_USE_BUF
#define BCD_InitIndexBuf(i)                  i = 0;
#define BCD_SaveDataInBuf(value, buf, i)     buf[i++] = value;
#define BCD_AddEndStrInBuf(value, buf, i)    buf[i] = 0;
#define BCD_SIZE_BUF 12
static volatile uint8_t buf[BCD_SIZE_BUF];
static uint8_t i;
#else
#define BCD_InitIndexBuf(i)
#define BCD_SaveDataInBuf(value, buf, i)
#define BCD_AddEndStrInBuf(value, buf, i)
#endif


#define BCD_Calc(digit, value, flag, buf, i, number)    do{digit = 0;                                        \
	while(value >= number){digit++; value -= number;}   \
	if (digit) {digit += BCD_SYMBOL; flag = BCD_SYMBOL;}\
	else {digit = flag;}                                \
	BCD_SaveDataInBuf(digit, buf, i);                   \
	BCD_SendData(digit); }while(0)

uint8_t* BCD_GetPointerBuf(void)
{
	#ifdef BCD_USE_BUF
	return (uint8_t*)buf;
	#else
	return (uint8_t *)0;
	#endif
}

/****************************************************************************/

void BCD_1(uint8_t value)
{
	BCD_InitIndexBuf(i);
	
	value += BCD_SYMBOL;
	
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_2(uint8_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;
	
	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 10);

	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_3(uint8_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
}

/***************************************************************************/

void BCD_3Int(uint16_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_4Int(uint16_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 1000);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_5Int(uint16_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 10000);
	BCD_Calc(digit, value, flag, buf, i, 1000);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

/****************************************************************************/

void BCD_Uchar(uint8_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;
	
	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_Uint(uint16_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 10000);
	BCD_Calc(digit, value, flag, buf, i, 1000);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}

void BCD_Ulong(uint32_t value)
{
	uint8_t digit, flag;
	
	flag = SYMB_NULL;

	BCD_InitIndexBuf(i);
	BCD_Calc(digit, value, flag, buf, i, 1000000000);
	BCD_Calc(digit, value, flag, buf, i, 100000000);
	BCD_Calc(digit, value, flag, buf, i, 10000000);
	BCD_Calc(digit, value, flag, buf, i, 1000000);
	BCD_Calc(digit, value, flag, buf, i, 100000);
	BCD_Calc(digit, value, flag, buf, i, 10000);
	BCD_Calc(digit, value, flag, buf, i, 1000);
	BCD_Calc(digit, value, flag, buf, i, 100);
	BCD_Calc(digit, value, flag, buf, i, 10);
	
	value += BCD_SYMBOL;
	BCD_SaveDataInBuf(value, buf, i);
	BCD_AddEndStrInBuf(0, buf, i);
	BCD_SendData(value);
}
#endif