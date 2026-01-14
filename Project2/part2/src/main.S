.text
.global main

.equ SWITCHES,0x41220000
.equ BUTTONS,0x41200000
.equ LEDS, 0x41210000

@blinks the led!
main:
	blinky_loop:
		bl led0_toggle
		movw r0,#0 @load lower bits of r0 with 0
		movt r0,#0x5000 @load top 16 bits with 0x3000
		@ Note: the above two instructions can be replaced with the psuedoinstruction
		@ ldr r0,=0x30000000. The assembler will replace the psuedoinstruction with the
		@ two mov instructions.
		bl delay 
	b blinky_loop

delay:
	subs r0,r0,#1
	bne delay
	bx lr

     led0_toggle:
        ldr r1,=LEDS
        ldr r0,[r1]
        eor r0,r0,#1
        str r0, [r1]
    bx lr

.end