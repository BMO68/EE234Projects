.text
.global main

.equ SWITCHES,0x41220000
.equ BUTTONS,0x41200000
.equ LEDS,0x41210000


@BGR 1
.equ B1_EN,0x43C00000
.equ G1_EN,0x43C00010
.equ R1_EN,0x43C00020

.equ B1_PERIOD,0x43C00004
.equ B1_WIDTH,0x43C00008
.equ G1_PERIOD,0x43C00014
.equ G1_WIDTH,0x43C00018
.equ R1_PERIOD,0x43C00024
.equ R1_WIDTH,0x43C00028


@BGR 2
.equ B2_EN,0x43C00030
.equ G2_EN,0x43C00040
.equ R2_EN,0x43C00050

.equ B2_PERIOD,0x43C00034
.equ B2_WIDTH,0x43C00038
.equ G2_PERIOD,0x43C00044
.equ G2_WIDTH,0x43C00048
.equ R2_PERIOD,0x43C00054
.equ R2_WIDTH,0x43C00058

@ enables led given
@ in: r0, pointer to address
@ out: N/A
BRG_ON: 
    mov r1,#1
    str r1,[r0]
bx lr


@ disables led given
@ in: r0, pointer to address
@ out: N/A
BRG_OFF:
    mov r1,#0
    str r1,[r0]
bx lr


@ set PWM window width
@ in: r0, pointer to address; r1, immediate value
@ out: N/A
SET_PWM_WINDOW:
    str r1,[r0]
bx lr

@ set PWM duty value
@ in: r0, pointer to address; r1, immediate value
@ out: N/A
SET_PWM_DUTY:
    str r1,[r0]
bx lr

@ grabs and sorts SWITCHES
@ in: r0, immediate value (of switches)
@ out: r3, register (upper 4 switches); r4, register (lower 4 switches)
SWITCH_SORT:

    @ catching upper 3 switches    
    mov r3,#0xfffff20
    and r3,r3,r0
       
    @ catching lower 5 switches
    mov r4,#0x0000001f
    and r4,r4,r0
    

bx lr


main:

    ldr r0,=SWITCHES
    ldr r0,[r0]
    @SWITCH_SORT


mov r0,#0
mov r7,#1
svc 0

.end