.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000
.set BUTTONS, 0x41200000

main:

    ldr r1,=LED_CTL
    ldr r2,=SW_DATA
    ldr r3,=BUTTONS

    loop:
        ldr r0,[r2]
        and r0,#0x0F
        ldr r4,[r3]
        and r4,#0x0F
        eor r0,r0,r4

        str r0,[r1]

        b loop

        @mov r4,#0x01
        @cmp r0,r4
        @beq led1on

        @mov r4,#0x02
        @cmp r0,r4
        @beq led2on

        @mov r4,#0x04
        @cmp r0,r4
        @beq led3on

        @mov r4,#0x08
        @cmp r0,r4
        @beq led4on
    
        @mov r4,#0x0
        @str r4,[r1]

    @b loop 
    
        @led1on:
         @   mov r4,#0x01
          @  str r4,[r1]
           @ b loop

  @      led2on:
   @         mov r4,#0x02 
    @        str r4,[r1]
     @       b loop

      @  led3on:
    @        mov r4,#0x04
     @       str r4,[r1]
      @      b loop

     @   led4on:
      @      mov r4,#0x08
       @     str r4,[r1]
        @    b loop
        
.end