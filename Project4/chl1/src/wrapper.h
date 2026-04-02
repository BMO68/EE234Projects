#ifndef WRAPPER_H

#define WRAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void configure_uart1(void);

char* integer_to_hex(int number);

void send_to_pc(char* string);

#endif