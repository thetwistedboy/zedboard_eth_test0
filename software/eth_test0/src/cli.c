
#include "cli.h"
#include "eth.h"
#include "uart.h"

#include <stdbool.h>

#define EMBEDDED_CLI_IMPL
#include "embedded_cli.h"




// CLI Globals //
// CLI memory allocation
#define CLI_BUFFER_SIZE_BYTES 4096
CLI_UINT ethcli_buffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE_BYTES)];
CLI_UINT uartcli_buffer[BYTES_TO_CLI_UINTS(CLI_BUFFER_SIZE_BYTES)];

// CLI instances
EmbeddedCli *ethcli;
EmbeddedCli *uartcli;


void cli_writechar(EmbeddedCli *cli, char c){
    (void) cli;

    if(cli == ethcli){
        ethcli_write_char(c);
    }
    
    if(cli == uartcli){
        uart_putchar(c);
    }
}

static void cli_idn_handler(EmbeddedCli *cli, char *args, void *context){
    (void) cli;
    (void) args;
    (void) context;
}

static void cli_echo_handler(EmbeddedCli *cli, char *args, void *context){
    (void) cli;
    (void) args;
    (void) context;
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
    // Create and configure the ethernet instance
    network_init();
    start_tcp_listen();

    // Create and configure UART instance
    uart_initialize();
    
    // Create and configure the ethernet CLI instance
    EmbeddedCliConfig *ethcli_config = embeddedCliDefaultConfig();
    ethcli_config->maxBindingCount = 16;
    ethcli_config->cliBuffer = ethcli_buffer;
    ethcli_config->enableAutoComplete = false;
    ethcli_config->cliBufferSize = CLI_BUFFER_SIZE_BYTES;

    ethcli = embeddedCliNew(ethcli_config);
    ethcli->writeChar = cli_writechar;

    cli_register_cmds(ethcli);

    // Create and configure the ethernet CLI instance
    EmbeddedCliConfig *uartcli_config = embeddedCliDefaultConfig();
    uartcli_config->maxBindingCount = 16;
    uartcli_config->cliBuffer = uartcli_buffer;
    uartcli_config->enableAutoComplete = false;
    uartcli_config->cliBufferSize = CLI_BUFFER_SIZE_BYTES;

    uartcli = embeddedCliNew(uartcli_config);
    uartcli->writeChar = cli_writechar;

    cli_register_cmds(uartcli);

    return 0;
}

int cli_process(void){
    // CLI process, call this in the main loop //
    
    // Check ethernet packet activity
    eth_process();

    // Handle CLI interface commands
    embeddedCliProcess(ethcli);
    
    if(uart_isRxAvailable()){
        embeddedCliReceiveChar(uartcli, uart_getchar());
    }
    embeddedCliProcess(uartcli);

    return 0;
}


