.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000


main:
    ldr r1,=LED_CTL
    ldr r2,=SW_DATA

    loop:

        ldr r0,[r2]
        and r0,#0x0F

        mov r4,#0x0
        str r4,[r1]

        mov r4,#4
        cmp r0,r4
        blt led1on

        mov r4,#8
        cmp r0,r4
        blt led2on

        mov r4,#12
        cmp r0,r4
        blt led3on
        
        mov r4,#16
        cmp r0,r4
        blt led4on

    b loop    


        led1on:
            mov r4,#0x01            
            str r4,[r1]
        b loop

        led2on:
            mov r4,#0x02
            str r4,[r1]
        b loop

        led3on:
            mov r4,#0x04
            str r4,[r1]
        b loop

        led4on:
            mov r4,#0x08
            str r4,[r1]
        b loop


.end