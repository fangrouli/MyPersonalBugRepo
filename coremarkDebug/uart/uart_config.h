
#ifndef _UART_CONF_H
#define _UART_CONF_H

#define TRUE   1
#define FALSE  0
#define ERROR -1

typedef unsigned int U32;        //U32 is 32-bit length

#define UART_ADDR					0x54000000
#define SIM_FINISH_ADDR   0x70707070

#define UART_TXFIFO				0x00
#define UART_RXFIFO 		 	0x04
#define UART_TXEN		 			0x08
#define UART_TXMARK 			0x0a
#define UART_RXEN		 			0x0c
#define UART_RXMARK 			0x0e

#define UART_IE						0x10
#define UART_IP						0x14
#define UART_DIV					0x18
#define UART_PARITY				0x1c
#define UART_WIRE4				0x20
#define UART_EITHER8OR9		0x24 \

#define uartaddr32(offset)  ((volatile U32 *)(UART_ADDR + offset))
#define simendaddr32(offset)  ((volatile U32 *)(SIM_FINISH_ADDR + offset))

#define BAUDRATE 115200
//#define CPU_FREQ 100000000
//#define DIVISOR 868 //10000000/115200 -1
#define CPU_FREQ 50000000
#define DIVISOR 434

/*Function declaration*/
//void pcie_phy_initial(void);
void UartStdOutInit(void);
unsigned char uartputchar(unsigned char my_ch);
void UartEndSimulation(void);
void uartprint(unsigned char *p);
void uartprint_uint_bin(unsigned int num);
unsigned char uartgetchar(void);
void uartdelay(int i);

#endif
