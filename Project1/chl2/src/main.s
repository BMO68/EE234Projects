.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000
.set BUTTONS, 0x41200000


main:

    ldr r1,=LED_CTL
    ldr r2,=SW_DATA
    ldr r3,=BUTTONS
    
    mov r5,#0x00
    str r5,[r1]
    
    loop:
        
        ldr r0,[r2]
        and r0,r0,#0x0FF
        
        ldr r4,[r3]
        and r4,r4,#3

        cmp r4,#0x001
        beq store

        cmp r4,#0x002
        beq reset
    
    b loop

        store:
            str r0,[r1]
        b loop
        
        reset:
            mov r5,#0x00
            str r5,[r1]
        b loop                

.end