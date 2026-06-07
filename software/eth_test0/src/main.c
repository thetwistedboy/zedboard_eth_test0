#include <stdio.h>

#include "xparameters.h"
#include "xil_printf.h"

#include "cli.h"

int main(void){
    cli_initialize();

    while(1){
        cli_process();
    }
    
    return 0;
}