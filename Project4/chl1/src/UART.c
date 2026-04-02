#include "wrapper.h"

//uart1 control register
#define UART1_CR *((uint32_t*)0xE0001000)

//uart1 mode register
#define UART1_MR *((uint32_t*)0xE0001004)

#define UART1_BAUDGEN *((uint32_t*)0xE0001018)
#define UART1_BAUDDIV *((uint32_t*)0xE0001034)
#define UART1_FIFO *((uint32_t*)0xE0001030)

//Switches and LEDs
#define LED_CTL *((uint32_t*)0x41210000)
#define SW_DATA *((uint32_t*)0x41220000)


void configure_uart1(void){
    UART1_CR = 0x03;

    UART1_MR = 0x20;

    UART1_BAUDGEN = 0x7C;

    UART1_BAUDDIV = 0x06;
}

char* integer_to_hex(int number) {
    char* string = (char*)malloc(10);
    sprintf(string,"%X", number);
    return string;
}

void send_to_pc(char* string) {
    for(int i = 0; string[i] != '\0'; i++) {
        UART1_FIFO = string[i];
    }
}