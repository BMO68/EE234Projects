#include "wrapper.h"

int main(){

    configure_uart1();

    disable_arm_interrupts();

    /* register handler into IRQ slot (exception ID 5) */
    Xil_ExceptionRegisterHandler(5, my_handler, NULL);

    configure_gic_uart1();
    configure_uart1_interrupt();

    enable_arm_interrupts();

    for(;;);
    
   return 1; 
} 