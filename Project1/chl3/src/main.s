.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000
.set BUTTONS, 0x41200000
.equ G_PERIOD, 0x43C00014
.equ G_WIDTH, 0x43C00018
.equ G_EN, 0x43C00010


main:

    LDR r0, =G_PERIOD
    LDR r1, =1024
    STR r1, [r0]

    LDR r0, =G_WIDTH    
    STR r1, [r0]      


    loop:
        
        LDR r0, =BUTTONS
        LDR r0, [r0]
        MOV r1, #1
        CMP r0, r1
        BEQ G_TOGGLE
        
    b loop     
    
        G_TOGGLE:
            ldr r0,=G_EN
            ldr r1,[r0]
            eor r1,r1,#1
            str r1,[r0]
        b loop
        
.end