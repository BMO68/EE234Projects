#include <stdint.h>

extern void configure_uart1(void);

extern void send_string(char str[]);

extern void receive_string(char str[]);


int main(){

    char str[128];

    configure_uart1();

    receive_string(str);

    send_string(str);

   return 1; 
}