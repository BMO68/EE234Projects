.text
.global main


main:
	bl configure_uart1
	
	mov r0,#70	@copy ascii 'F' to r0
	bl uart1_send_char	@send the data in r0 over uart

	b .	@endless loop