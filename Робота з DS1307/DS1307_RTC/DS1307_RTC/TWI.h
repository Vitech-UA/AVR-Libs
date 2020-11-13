


#ifndef TWI_H_
#define TWI_H_
#include "main.h"

void I2C_Init(void); //Ініціалізація інтерфейсу
void I2C_StartCondition(void);
void I2C_StopCondition(void);
void I2C_SendByte(unsigned char c);
void I2C_SendByteAdress(unsigned char c, unsigned char addr);
unsigned char I2C_ReadByte(void);
unsigned char I2C_ReadLastByte(void);

#endif /* TWI_H_ */