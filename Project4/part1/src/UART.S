.text

@uart1 control register
.equ UART1_CR, 0xE0001000
@uart1 mode register
.equ UART1_MR, 0xE0001004

.equ UART1_BAUDGEN, 0xE0001018
.equ UART1_BAUDDIV, 0xE0001034
.equ UART1_FIFO, 0xE0001030


@Write a function that configures the Zynq’s UART 1 module for 115200 baud, 8 data bits, one stop bit, and no parity (refer to the reference manual page to learn which registers must be programmed). After configuring the UART, send a character to your PC by writing an ASCII character to the UART data FIFO. After sending the character, enter an endless loop. When you run the program, the sent character should appear on the Vitis terminal.

@To send the character, write a function that takes in a one-byte ASCII character as a parameter. Make sure you check the UART FIFO transmit status before placing the data in the FIFO, and wait for it to be ‘not full’ before writing to the UART FIFO.


@Resets the UART
.global reset_uart1
reset_uart1:
	ldr r1,=UART1_CR

	mov r0, #3	@assert reset
	str r0,[r1]


bx lr

@Configuring the UART
.global configure_uart1
configure_uart1:
	push {lr} @push lr for subroutine call

	bl reset_uart1 @reset the module
	
	ldr r1, =UART1_MR

	@configure the mode register
	@normal mode bits [9:8] = 2b00
	@one stop bit, bits [7:6] = 2b00
	@8 data bits, bits [2:1] = 2b0x
	@use reference clock, bit0 = 0
	@disable parity, bits[5:3] = 3b1xx
	@6b100000 == 0x20

	mov r0, #0x20

	str r0,[r1]

	ldr r1, =UART1_CR
	
	mov r0,#4 @set bit 2 to enable tx
	orr r0,r0,#16 @set bit 4 to enable rx
	
	str r0,[r1] @write back to CR
	
    @Set baud rate
    ldr r1,=UART1_BAUDGEN
    mov r0,#0x7C
    str r0,[r1]
    
    @Set baud rate divider
    ldr r1,=UART1_BAUDDIV
    mov r0, #0x6
    str r0,[r1]
    
	pop {lr} @restore return address
bx lr @return


@Sends the character to the pc
.global uart1_send_char
uart1_send_char:
    ldr r1,=UART1_FIFO
	str r0,[r1]
bx lr @return