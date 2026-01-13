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
        LDR r2, [r0]
        MOV r1, #1
        CMP r2, r1
        BEQ G_On

        LDR r0, =G_EN
        MOV r1, #0x0
        STR r1, [r0]
    b loop     
    
        G_On:
            LDR r0, =G_EN
            LDR r1, =1
            STR r1, [r0]
        b loop
        
.end