#include "xil_types.h"

int uart_initialize(void);

void uart_putchar(char);
char uart_getchar(void);
u8 uart_isRxAvailable(void);