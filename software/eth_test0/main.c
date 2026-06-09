#include <stdio.h>
#include <xil_exception.h>
#include <xscugic_hw.h>
#include <xstatus.h>

#include "xparameters.h"
#include "xil_printf.h"
#include "sleep.h"
#include "xscugic.h"

#include "cli.h"



int main(void){
    xil_printf("\r\n\r\nStarting... \n\r");
    
    cli_initialize();

    while(1){
        cli_process();
    }
    
    return 0;
}