[bits 16]

print_string:
	pusha
	mov ah, 0xe
	loop_print_string:
	mov al, [bx]
	cmp al, 0
	je end_print_string
	int 0x10
	add bx, 1
	jmp loop_print_string
	end_print_string:
	popa
	ret