[bits 16]

;Include the kernel_size.asm file wich will be rewrited by the Makefile to calculated the number of
; needed sector to load the whole kernel in RAM
%include "bootloader/kernel_size.asm"

load_kernel:
    mov bx, LOADING_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET
    mov dl, [BOOT_DRIVE]
    mov dh, kernel_size ; Get the macro kernel_size calculated by the Makefile
    call read_in_disk
    
    ret

read_in_disk:
    pusha
    push dx

    mov ah, 0x02 ; bios instr to read

    mov al, dh
    mov cl, 0x02 ; start reading at sector 2
    mov ch, 0x00
    mov dh, 0x00
    int 0x13 ; bios instr to read
    jc disk_error

    pop dx
    cmp dh, al
    jne disk_error
    popa
    ret

disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $ ; hang here