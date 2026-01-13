.text
.global main

.equ LED, 0x41210000
.set BUTTON, 0x41200000

main:
    ldr r1,=LED
    ldr r2,=BUTTON

    loop:
        ldr r0,[r2]
        str r0,[r1]
        b loop

.end