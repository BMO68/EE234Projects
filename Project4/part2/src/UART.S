.text
.global reset_uart1
.global configure_uart1
.global read_character_uart1
.global led_state
.global toggle_led


@uart1 control register
.equ UART1_CR, 0xE0001000
@uart1 mode register
.equ UART1_MR, 0xE0001004

.equ UART1_BAUDGEN, 0xE0001018
.equ UART1_BAUDDIV, 0xE0001034
.equ UART1_FIFO, 0xE0001030

@Switches and LEDs
.equ LED_CTL, 0x41210000
.equ SW_DATA, 0x41220000


@Resets the UART
reset_uart1:
	ldr r1,=UART1_CR

	mov r0, #3	@assert reset
	str r0,[r1]


bx lr

@Configuring the UART
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

@Reads a character from the UART port
read_character_uart1:

	ldr r1,=UART1_FIFO
	ldr r0,[r1]

bx lr

@Turns on / off the LEDs
@receiving 'a' turns on led0, receiving 'b' turns on led1, receiving 'c' turns on led2, receiving 'd' turns on led3
led_state:
	push {lr}
	
	cmp r0,#0x61
	moveq r2,#0x01
	bleq toggle_led

	cmp r0,#0x62
	moveq r2,#0x02
	bleq toggle_led
	
	cmp r0,#0x63
	moveq r2,#0x04
	bleq toggle_led

	cmp r0,#0x64
	moveq r2,#0x08
	bleq toggle_led

	mov r0,#0x00

	pop {lr}
bx lr

@toggles leds
@r2 is led to toggle
toggle_led:
	
	ldr r1,=LED_CTL
	ldr r0,[r1]
	eor r0,r2
	str r0,[r1]
	
bx lr 