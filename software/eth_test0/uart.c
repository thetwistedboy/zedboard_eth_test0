

#include "uart.h"

#include "cli.h"

#include "xparameters.h"
#include "xuartps.h"
#include "xscugic.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "sleep.h"
#include <xstatus.h>
#include <xuartps_hw.h>

XUartPs uart1_instance;

int uart_initialize(void){
    int status = XST_SUCCESS;

    xil_printf("Initializing UART1... ");
    usleep(100000);
    
    XUartPs_Config *uart_config;
    uart_config = XUartPs_LookupConfig(XPAR_UART1_BASEADDR);
    status = XUartPs_CfgInitialize(&uart1_instance, uart_config, uart_config->BaseAddress);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }
    XUartPs_SetBaudRate(&uart1_instance, 115200);

    xil_printf("Success!\r\n");
    
    return status;
}

void uart_putchar(char c){
    
    XUartPs_SendByte(uart1_instance.Config.BaseAddress, c);

}

char uart_getchar(void){
    
    return XUartPs_RecvByte(uart1_instance.Config.BaseAddress);

}

u8 uart_isRxAvailable(void){

    return XUartPs_IsReceiveData(uart1_instance.Config.BaseAddress);

}

u8 uart_isTxAvailable(void){
    return XUartPs_IsTransmitFifoEmpty(uart1_instance.Config.BaseAddress);
}

int uart1_RegisterInterrupt(XScuGic *intc_instance){
    int status;
    status = XScuGic_Connect(intc_instance, XPAR_XUARTPS_1_INTR, (Xil_ExceptionHandler)uart1_irq_handler, NULL);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }


    XScuGic_SetPriorityTriggerType(intc_instance, XPAR_XUARTPS_1_INTR, 0xA0, 0x01);
    XUartPs_SetInterruptMask(&uart1_instance, XUARTPS_IXR_RXOVR | XUARTPS_IXR_TOUT);
    
    XScuGic_Enable(intc_instance, XPAR_XUARTPS_1_INTR);

    return XST_SUCCESS;
}

void uart1_irq_handler(void *CallBackRef){
    uartcli_rxbyte();
}