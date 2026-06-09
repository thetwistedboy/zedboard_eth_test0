#include "xparameters.h"
#include "xil_printf.h"
#include "xscugic.h"
#include "xuartps.h"

#include "cli.h"

#include <xil_exception.h>
#include <xparameters_ps.h>

XScuGic intc_instance;

int setup_intc(void){
    int status;
    
    XScuGic_Config *intc_config;
    intc_config = XScuGic_LookupConfig(XPAR_XSCUGIC_0_BASEADDR);
    if(intc_config == NULL){
        return XST_FAILURE;
    }

    status = XScuGic_CfgInitialize(&intc_instance, intc_config, intc_config->CpuBaseAddress);
    if(status != XST_SUCCESS){
        return XST_FAILURE;
    }

    Xil_ExceptionInit();
    
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, &intc_instance);

    

    Xil_ExceptionEnable();

    return status;
}