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
SET_PWM_FREQ:
    str r1,[r0]
bx lr

@ set PWM duty value
@ in: r0, pointer to address; r1, immediate value
@ out: N/A
SET_PWM_WINDOW:
    str r1,[r0]
bx lr

@ grabs and sorts SWITCHES
@ in: r0, immediate value (of switches)
@ out: r3, register (upper 3 switches); r4, register (lower 5 switches)
SWITCH_SORT:

    @ catching upper 3 switches    
    mov r3,#0b11100000000
    and r3,r3,r0
    asr r3,r3,#8
       
    @ catching lower 8 switches
    mov r4,#0b11111111
    and r4,r4,r0
    

bx lr


main:

    @start blue led
    ldr r0,=B1_PERIOD @set B frequency
    mov r1,#0b11111111
    bl SET_PWM_FREQ
    
    mov r1,#0b11111111
    ldr r0,=B1_WIDTH @set B width
    B1_WIDTH:
    bl SET_PWM_WINDOW
    sub r1,r1,#1
    cmp r1,#0
    bne B1_WIDTH

    ldr r0,=B1_EN
    bl BRG_ON
    @end blue led

    @start green
    ldr r0,=G1_PERIOD @set G frequency
    mov r1,#0b11111111
    bl SET_PWM_FREQ
    
    mov r1,#0b1111111
    G1_WIDTH:
    ldr r0,=G1_WIDTH @set G width
    bl SET_PWM_WINDOW
    sub r1,r1,#1
    cmp r1,#0
    bne G1_WIDTH

    ldr r0,=G1_EN
    bl BRG_ON
    @end green

    @start red   
    ldr r0,=R1_PERIOD @set R frequency
    mov r1,#0b11111111
    bl SET_PWM_FREQ
    
    mov r1,#0b11111111
    R1_WIDTH:
    ldr r0,=R1_WIDTH @set R width
    bl SET_PWM_WINDOW
    sub r1,r1,#1
    cmp r1,#0
    bne R1_WIDTH

    ldr r0,=R1_EN
    bl BRG_ON
    @end red

b main

mov r0,#0
mov r7,#1
svc 0

.end