#ifndef UART_H
#define UART_H

#include "xil_types.h"
#include "xscugic.h"

int uart_initialize(void);

void uart_putchar(char);
char uart_getchar(void);
u8 uart_isRxAvailable(void);
u8 uart_isTxAvailable(void);

int uart1_RegisterInterrupt(XScuGic *intc_instance);
void uart1_irq_handler(void *CallBackRef);

#endif