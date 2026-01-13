.text
.global main

.equ SWITCHES,0x41220000
.equ BUTTONS,0x41200000
.equ LEDS, 0x41210000

main:

    led0_off:
        ldr r0,=0
        ldr r1,=LEDS
        str r0,[r1]
    bx lr

    led0_on:
        ldr r0,=1
        ldr r1,=LEDS
        str r0,[r1]
    bx lr

.end