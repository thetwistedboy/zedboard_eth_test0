#ifndef ETH_H
#define ETH_H

#include "xil_types.h"
#include "lwip/tcp.h"

void network_init(void);
void start_tcp_listen(void);

void eth_process(void);

err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t tcp_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err);

void eth_putchar(char c);
char eth_getchar(void);
u8 eth_isRxAvailable(void);

#endif