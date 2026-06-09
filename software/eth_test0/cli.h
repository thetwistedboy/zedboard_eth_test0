#ifndef CLI_H
#define CLI_H


#include "xparameters.h"

#include "embedded_cli.h"

int cli_initialize(void);
int cli_process(void);

void uartcli_rxbyte(void);

#endif