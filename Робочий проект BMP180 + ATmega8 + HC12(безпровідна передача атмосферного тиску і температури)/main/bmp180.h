


#ifndef BMP180_H_
#define BMP180_H_

#include "main.h"

uint16_t Read(uint8_t address);
void BMP180_Calibration (void);
void BMP180_get_temper(void);
void BMP180_get_pressure(void);
void BMP180_calculation (int32_t* temperature, int32_t* pressure);
void bmp180CalcAltitude(int32_t pressure);




#endif /* BMP180_H_ */