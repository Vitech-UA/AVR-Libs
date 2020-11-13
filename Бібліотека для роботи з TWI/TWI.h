


#ifndef TWI_H_
#define TWI_H_
#include "main.h"

void I2C_Init(void); //Ініціалізація інтерфейсу
void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(unsigned char c);



#endif /* TWI_H_ */