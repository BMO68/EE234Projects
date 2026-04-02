#include "wrapper.h"

int main(void) {

    configure_uart1();

    int number = 10;
    char* string = integer_to_hex(number);

    send_to_pc(string);

    return 0;
}