

#include "uart.h"

#include "xparameters.h"
#include "xuartps.h"
#include "xil_printf.h"
#include "xil_types.h"
#include <xstatus.h>
#include <xuartps_hw.h>

XUartPs uart;

int uart_initialize(void){
    int status = XST_SUCCESS;
    
    XUartPs_Config *uart_config;
    uart_config = XUartPs_LookupConfig(XPAR_UART1_BASEADDR);
    status = XUartPs_CfgInitialize(&uart, uart_config, uart_config->BaseAddress);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }

    return status;
}

void uart_putchar(char c){

    XUartPs_SendByte(uart.Config.BaseAddress, c);

}

char uart_getchar(void){
    
    return XUartPs_RecvByte(uart.Config.BaseAddress);

}

u8 uart_isRxAvailable(void){

    return XUartPs_IsReceiveData(uart.Config.BaseAddress);

}