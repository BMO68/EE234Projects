#include "wrapper.h"

int main(){

    char str[128];

    configure_uart1();

    receive_string(str);

    send_string(str);

   return 1; 
}