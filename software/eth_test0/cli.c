
#include "cli.h"
#include "eth.h"
#include "uart.h"

#include "sleep.h"
#include <stdbool.h>

#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"


// CLI Globals //
// CLI memory allocation
#define CLI_BUFFER_SIZE_BYTES 4096
CLI_UINT ethcli_buffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE_BYTES)];
CLI_UINT uartcli_buffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE_BYTES)];

// CLI instances
EmbeddedCli *ethcli_instance;
EmbeddedCli *uartcli_instance;


void cli_writechar(EmbeddedCli *cli, char c){
    (void) cli;

    if(cli == ethcli_instance){
        eth_putchar(c);
    }
    
    if(cli == uartcli_instance){
        uart_putchar(c);
    }
}

static void cli_idn_handler(EmbeddedCli *cli, char *args, void *context){
    (void) cli;
    (void) args;
    (void) context;
    
    xil_printf("I am a Zynq 7000!\r\n");

    return;
}

static void cli_echo_handler(EmbeddedCli *cli, char *args, void *context){
    (void) cli;
    (void) context;

    xil_printf("%s", args);

    return;
}

const CliCommandBinding cmd_list[] = {
    {
        .name = "idn",
        .help = "Prints ID info",
        .tokenizeArgs = false,
        .context = NULL,
        .binding = cli_idn_handler
    },
    {
        .name = "echo",
        .help = "Echos any text argument fed to it | echo \"any string here\"",
        .tokenizeArgs = false,
        .context = NULL,
        .binding = cli_echo_handler
    }
};

static int cli_register_cmds(EmbeddedCli *cli){
    for(unsigned int i = 0; i < sizeof(cmd_list)/sizeof(cmd_list[0]); i++){
        embeddedCliAddBinding(cli, cmd_list[i]);
    }

    return 0;
}

int cli_initialize(void){
    
    // Create and configure UART instance
    uart_initialize();

    // Create and configure the ethernet instance
    network_init();
    start_tcp_listen();
    //while(uart_isTxAvailable()){};
    
    // Create and configure the ethernet CLI instance
    xil_printf("Initializing CLI instances... ");
    usleep(100);
    EmbeddedCliConfig *ethcli_config = embeddedCliDefaultConfig();
    ethcli_config->maxBindingCount = 16;
    ethcli_config->cliBuffer = ethcli_buffer;
    ethcli_config->enableAutoComplete = false;
    ethcli_config->cliBufferSize = CLI_BUFFER_SIZE_BYTES;

    ethcli_instance = embeddedCliNew(ethcli_config);
    ethcli_instance->writeChar = cli_writechar;

    cli_register_cmds(ethcli_instance);

    // Create and configure the ethernet CLI instance
    EmbeddedCliConfig *uartcli_config = embeddedCliDefaultConfig();
    uartcli_config->maxBindingCount = 16;
    uartcli_config->cliBuffer = uartcli_buffer;
    uartcli_config->enableAutoComplete = false;
    uartcli_config->cliBufferSize = CLI_BUFFER_SIZE_BYTES;

    uartcli_instance = embeddedCliNew(uartcli_config);
    uartcli_instance->writeChar = cli_writechar;

    cli_register_cmds(uartcli_instance);
    
    xil_printf("Success!\r\n");

    return 0;
}

int cli_process(void){
    // CLI process, call this in the main loop //
    
    // Check ethernet packet activity
    eth_process();

    // Handle CLI interface commands
    if(eth_isRxAvailable()){
        embeddedCliReceiveChar(ethcli_instance, eth_getchar());
    }
    embeddedCliProcess(ethcli_instance);
    
    /*if(uart_isRxAvailable()){
        embeddedCliReceiveChar(uartcli_instance, uart_getchar());
    }*/
    embeddedCliProcess(uartcli_instance);

    return 0;
}

void uartcli_rxbyte(void){
    
    embeddedCliReceiveChar(uartcli_instance, uart_getchar());

    return;
}
