/*
 * usart.h
 *
 * Created: 07.10.2017 20:18:07
 *  Author: Admin
 */ 


#ifndef USART_H_
#define USART_H_

#include "main.h"

void USART_Transmit(unsigned char data);
void USART_ini();
void usart_putline(char *buffer);

#endif /* USART_H_ */