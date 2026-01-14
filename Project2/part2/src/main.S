.text
.global main

.equ SWITCHES,0x41220000
.equ BUTTONS,0x41200000
.equ LEDS, 0x41210000

@blinks the led!
main:
	blinky_loop:
		bl led0_toggle
		bl switch_count
		
		ldr r0,[r0]
		lsl r0,#20
		mov r1,r0
		
		bl delay 
	b blinky_loop

mov r7,#1
swi 0

delay:
	subs r1,r1,#1
	bne delay
	bx lr

led0_toggle:
    ldr r1,=LEDS
    ldr r0,[r1]
    eor r0,r0,#1
	str r0, [r1]
	bx lr

switch_count:
	ldr r0,=SWITCHES
	ldr r0,[r0]
	bx lr

.end