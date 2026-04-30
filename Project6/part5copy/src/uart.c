#include "uart.h"
#include <stdint.h>

void configure_uart1(){
    uint32_t *datapath;

    datapath = (uint32_t *)UART1_MR;
    *datapath = 0x00000020;  // Configure Mode Register

    datapath = (uint32_t *)UART1_CR;
    *datapath = (1 <<8 ) | (1 << 9); //RSTTX + RSTRX
    *datapath = (1 << 4) | (1 << 2) | (1 <<0);  // Configure Control Register: tx en | rx en | uart en

    datapath = (uint32_t *)UART1_BAUDGEN;
    *datapath = 124; // Set Baud Rate Generator

    datapath = (uint32_t *)UART1_BAUDDIV;
    *datapath = 6;   // Set Baud Rate Divider
}

char uart1_getchar(){
    uint32_t *datapath;
    uint32_t temp_data;

    do{
        datapath = (uint32_t *)UART1_SR;
        temp_data = *datapath;
        temp_data &= 2;
    } while(temp_data == 2);

    datapath = (uint32_t *)UART1_FIFO;
    temp_data = *datapath;
    return temp_data;  // Return received character
}

void uart1_sendchar(char data){
    uint32_t *datapath;
    uint32_t temp_data;

    do {
        datapath = (uint32_t *)UART1_SR;
        temp_data = *datapath;
        temp_data &= 16;  // Check if TX FIFO is full
    } while(temp_data == 16);

    datapath = (uint32_t *)UART1_FIFO;
    *datapath = data;  // Send character
}

void uart1_sendstr(char buffer[]){
    int i = 0;
    while(buffer[i] != '\0'){
        uart1_sendchar(buffer[i]);
        i++;
    }
}

int uart1_getln(char buffer[], int max){
    int i = 0;
    char ch;
    while(i < max - 1){
        ch = uart1_getchar();
        if(ch == '\n' || ch == '\r'){
            break;
        }
        buffer[i++] = ch;
    }
    buffer[i] = '\0';  // Null-terminate the string
    return i;
}

void uart1_sendint(int value) {
    char buffer[12];   // large enough for -32768
    int i = 0;

    // Handle zero
    if (value == 0) {
        uart1_sendchar('0');
        return;
    }

    // Handle negative numbers
    if (value < 0) {
        uart1_sendchar('-');
        value = -value;
    }

    // Convert digits to characters (in reverse order)
    while (value > 0 && i < (int)sizeof(buffer)) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Send digits in correct order
    while (i > 0) {
        uart1_sendchar(buffer[--i]);
    }
}