#include "eth.h"

#include "xparameters.h"
#include "xil_types.h"
#include "xiltimer.h"
#include "xil_printf.h"
#include "sleep.h"

#include "lwip/init.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"
#include "lwip/dhcp.h"
#include "lwip/timeouts.h"
#include "netif/xadapter.h"

// Linking to embedded cli interface
#include "cli.h"

// Ethernet globals declarations
struct netif server_netif;
ip_addr_t ipaddr, netmask, gw;
volatile int dhcp_timoutcntr;

void network_init(void){
    unsigned char mac_ethernet_address[] = {0x00, 0x0A, 0x35, 0x00, 0x01, 0x02};
    // Initialize lwIP stack
    lwip_init();

    // Set static IP
    int ip[]        = { 192, 168,   1,  10 };
    int subnet[]    = { 255, 255, 255,   0 };
    int gateway[]   = { 192, 168,   1,   1 };
    
    IP4_ADDR(&ipaddr, ip[0], ip[1], ip[2], ip[3]);
    IP4_ADDR(&netmask, subnet[0], subnet[1], subnet[2], subnet[3]);
    IP4_ADDR(&gw, gateway[0], gateway[1], gateway[2], gateway[3]);

    // Add network interface
    xemac_add(&server_netif, &ipaddr, &netmask, &gw, mac_ethernet_address, XPAR_XEMACPS_0_BASEADDR);

    // Set as default and bring it up
    netif_set_default(&server_netif);
    netif_set_up(&server_netif);

    #if LWIP_DHCP == 1
    // DHCP checking
    xil_printf("DHCP Starting...\r\n");
    dhcp_start(&server_netif);
    
    dhcp_timoutcntr = 20;
    while(dhcp_timoutcntr > 0){
        // Poll the Ethernet interface for incoming packets
        xemacif_input(&server_netif);

        // DHCP Checking
        if (dhcp_supplied_address(&server_netif)) {
            xil_printf("DHCP Bound successfully!\r\n");
            xil_printf("IP Address: %d.%d.%d.%d\r\n", 
                ip4_addr1_16(&server_netif.ip_addr),
                ip4_addr2_16(&server_netif.ip_addr),
                ip4_addr3_16(&server_netif.ip_addr),
                ip4_addr4_16(&server_netif.ip_addr));
            break;
        }
        
        usleep(100);
        dhcp_timoutcntr--;
    }
    if (dhcp_timoutcntr <= 0){
        xil_printf("DHCP Timeout\r\n");
        xil_printf("Defaulting to:\r\n");
        xil_printf("IP:      %3d.%3d.%3d.%3d\r\n", ip[0], ip[1], ip[2], ip[3]);
        xil_printf("SUBNET:  %3d.%3d.%3d.%3d\r\n", subnet[0], subnet[1], subnet[2], subnet[3]);
        xil_printf("GATEWAY: %3d.%3d.%3d.%3d\r\n", gateway[0], gateway[1], gateway[2], gateway[3]);
    }
    #endif

}

void start_tcp_listen(void){
    struct tcp_pcb *pcb;
    err_t err;

    // 1. Create a new TCP PCB
    pcb = tcp_new();
    if (pcb == NULL) {
        return; // Handle memory error
    }

    // 2. Bind to any IP address on port 8080
    err = tcp_bind(pcb, IP_ADDR_ANY, 8080);
    if (err != ERR_OK) {
        tcp_close(pcb);
        return;
    }

    // 3. Start listening for connections
    pcb = tcp_listen(pcb);
    if (pcb == NULL) {
        return; // Handle memory error
    }

    // 4. Assign the accept callback
    tcp_accept(pcb, tcp_accept_callback);
}

void eth_process(void){
    // Poll the Ethernet interface for incoming packets
    xemacif_input(&server_netif);
    
    // Periodically call lwIP TCP timers
    sys_check_timeouts();
}

// Called when data is received from the client
err_t tcp_recv_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){
    (void) arg;
    (void) err;
    
    if (p == NULL) {
        // Connection was closed by the remote host
        tcp_close(tpcb);
        return ERR_OK;
    }

    // Process data in p->payload (p->len)
    
    // Acknowledge the received data segment
    tcp_recved(tpcb, p->tot_len);

    // Free the packet buffer
    pbuf_free(p);
    return ERR_OK;
}

// Called when a new connection is accepted
err_t tcp_accept_callback(void *arg, struct tcp_pcb *newpcb, err_t err){
    (void) arg;
    (void) err;
    
    // Set up what to do when data arrives
    tcp_recv(newpcb, tcp_recv_callback);
    return ERR_OK;
}

u32_t sys_now(void) {
    XTime tick;
    XTime_GetTime(&tick);
    
    // Convert Zynq CPU cycles to milliseconds
    return (u32_t)(tick / (COUNTS_PER_SECOND / 1000));
}

void ethcli_write_char(char c){
    (void) c;
}

char ethcli_read_char(){
    return '\0';
}