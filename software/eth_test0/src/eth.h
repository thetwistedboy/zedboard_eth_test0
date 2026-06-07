#ifndef ETH_H
#define ETH_H

#include "lwip/tcp.h"

void network_init(void);
void start_tcp_listen(void);

void eth_process(void);

err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t tcp_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err);

void ethcli_write_char(char c);
char ethcli_read_char();

#endif