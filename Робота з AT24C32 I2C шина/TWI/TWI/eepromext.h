/*
 * eepromext.h
 *
 * Created: 21.10.2017 13:00:41
 *  Author: Admin
 */ 


#ifndef EEPROMEXT_H_
#define EEPROMEXT_H_

#include "main.h"

#define TW_MT_DATA_ASK 0x28 //Ведучий передав дані і відомий підтвердив
#define TW_MR_DATA_ASK 0x50 //Ведучий прийняв дані і передав підтвердження
#define TW_MR_DATA_NASK 0x58 //Ведучий передав дані і відомий підтвердив

int EepromWriteByte(unsigned char c);
unsigned char EepromReadByte(void);
unsigned char EepromReadLastByte(void);

#endif /* EEPROMEXT_H_ */