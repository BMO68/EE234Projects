.text
.global main


@Write an assembly subroutine to read a character from the UART port. 
@Once called, the subroutine can check the FIFO status, and wait until there is at least one entry in the receive FIFO. 
@When data is available, read it, and pass it back to the calling program.

@Write a program that uses your read subroutine to receive a character from the UART port. 
@If an  'a' is received, toggle LED0 to its opposite state. If a 'b' is received, toggle LED1, if a 'c', toggle LED2, and if a 'd' toggle LED3. 
@Ignore any other characters. When an LEDs state is changed, send the number of the LED that was toggled to the PC's terminal.

main:

    bl configure_uart1

    loop:

        bl read_character_uart1

        bl led_state

b loop @end of program