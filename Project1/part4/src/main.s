.text
.global main

.equ LED_CTL, 0x41210000
.set SW_DATA, 0x41220000


main:
	ldr r1,=SW_DATA
	ldr r2,=LED_CTL

	loop:
		
		ldr r0, [r1]
		
		mov r4, #0x0FFF
		cmp r0, r4
		beq led2
			
		mov r4, #21
		cmp r0, r4
		beq led1
			
		mov r0, #0x00	
		str r0, [r2]
		
		b loop
		
		led2:
			mov r0, #0x02
			str r0, [r2]
			b loop
			
		led1:
			mov r0, #0x01
			str r0, [r2]
			b loop
			
		
.end
