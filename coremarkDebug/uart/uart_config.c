#include "uart_config.h"
#include <stdarg.h>

void UartStdOutInit(void)
{
  *uartaddr32(UART_DIV) = DIVISOR; //200MHz / 115200 Hz -1 = 1736
  *uartaddr32(UART_TXEN) = TRUE; // tx enabled, stop bit 1 bit
  *uartaddr32(UART_RXEN) = TRUE; //rx enabled
  return;
}

void UartEndSimulation(void)
{
  uartputchar((char) 0x4); // End of simulation
  //*simendaddr32(0x000) = 0xdeadbeef; 
  while(1);
}

unsigned char uartputchar(unsigned char c)
{
	while (*uartaddr32(UART_TXFIFO) >= (1<<31)){  //while full
		*simendaddr32(0x000) = 0xdeadbeef;
	}
	
	//uartdelay(100);
	if (c == '\n')
		uartputchar('\r');
	*uartaddr32(UART_TXFIFO) = c;
	return (c);
}

void uartprint(unsigned char *p)
{
	while (*p)
		uartputchar(*(p++));
}

void uartprint_uint_bin(unsigned int num)
{
	for (int i = 0; i < 32; i++, num <<= 1)
		uartputchar((num & 0x80000000) ? '1' : '0');
	uartputchar('\n');
}

unsigned char uartgetchar(void)
{
  return (*uartaddr32(UART_RXFIFO));
}


void uartdelay(int i){
	for (int j=0; j<i; j++){}
}


