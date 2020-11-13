//***************************************************************************
//
//  File........: bcd.с
//
//  Author(s)...: Pashgan ChipEnable.Ru
//
//  Target(s)...: для любого микроконтроллера
//
//  Compiler....: для любого компилятора 
//
//  Description.: библиотека для перевода двоичных чисел в символы и вывода их на жкд 
//
//  Revisions...: 
//
//  18.10.2009 - 1.0 - Создан                                       - Pashgan.
//
//***************************************************************************
#include "bcd2.h"
#include "lcd.h"

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

