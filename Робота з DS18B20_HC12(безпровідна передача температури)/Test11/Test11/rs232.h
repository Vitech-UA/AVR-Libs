#define UART_BAUDRATE	4800
#define UART_SETTING	8

int uart_getchar(void)
{
	// Проверяем, есть ли уже байт в буфере приемника
	if (bit_is_set(UCSRA, RXC) == 0)
		return -1;

	return UDR;
}

void uart_putchar(char c)
{
	// Ожидаем готовности буфера
	while (!(UCSRA & (1 << UDRE))) ;

	// Передача
	UDR = c;
}

void uart_getline(char *buffer)
{
	char c=0;
	while (c != 0x0D)
	{
		c = uart_getchar();
		if ( (c != -1) && (c != 0x0D) && (c != 0x0A))
		{
			*buffer = c;
			buffer++;
			// Внимание! Буфер должен быть достаточно большим,
			// иначе может возникнуть переполнение
		}
	}
	// Важно: окончание строки!
	*buffer = 0;
}

void uart_putline(char *buffer)
{
	while (*buffer!=0)
	{
		uart_putchar(*buffer);
		buffer++;
	}

	// Завершение строки символом возврата каретки, т.е. 0x0D и 0x0A
	uart_putchar(13);
	uart_putchar(10);
}

void uart_putstring(char *buffer)
{
	while (*buffer!=0)
	{
		uart_putchar(*buffer);
		buffer++;
	}
}

void setup_uart()
{
	UBRRH = (char) (UART_SETTING >> 8);
	UBRRL = (char) (UART_SETTING);
	
	// Включение приемника и передатчика
	UCSRB = (1<<RXEN) | (1<<TXEN);

	// Асинхронный режим, 8N1
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
}
