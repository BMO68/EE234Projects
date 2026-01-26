.text
.global main

.equ SWITCHES,0x41220000
.equ BUTTONS,0x41200000
.equ LEDS, 0x41210000


delay:
	subs r2,r2,#1
	bne delay
bx lr


led0_toggle:
    ldr r3,=LEDS
    ldr r2,[r3]
    eor r2,r2,#1
	str r2,[r3]
bx lr


switch_count:
	ldr r1,=SWITCHES
	ldr r1,[r1]
bx lr


led0_off:
	ldr r2,=0
	ldr r3,=LEDS
	str r2,[r3]
bx lr


led0_on:
	ldr r2,=1
	ldr r3,=LEDS    
	str r2,[r3]
bx lr


PWM:
		
	off:
		cmp r0,r1
		ble on
		subs r0,r0,#1
	b off

	on: @duty cycle loop
		mov r1,r14
		cmp r0,#0x0
		beq leave

		bl led0_on
		mov r14,r1
		subs r0,r0,#1
	b on

	leave:

bx lr


main:

blinky_loop:

	bl led0_off

	mov r0,#0x00000fff @set PWM window

	bl switch_count @grab switches with r1

	bl PWM @enter pulse width modulation
	
b blinky_loop

mov r7,#1
swi 0

.end