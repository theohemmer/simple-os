[bits 16]
[org 0x7c00]

KERNEL_OFFSET equ 0x8000

mov [BOOT_DRIVE], dl

mov bp, 0x1000 ; Stack base pointer
mov sp, bp

mov bx, STARTING_MSG
call print_string

call load_kernel

call switch_to_pm

%include "bootloader/gdt.asm"
%include "bootloader/switch_to_pm.asm"
%include "bootloader/print_string.asm"
%include "bootloader/load_kernel.asm"

[bits 32]
LANDED:
    call KERNEL_OFFSET

    jmp $

[bits 16]
BOOT_DRIVE      db 0
DISK_ERROR_MSG  db 'ERROR READING DISK. HANGING', 0ah, 0dh, 0
STARTING_MSG    db 'Starting UselessOS 0.1', 0ah, 0dh, 0
LOADING_KERNEL  db 'Loading the kernel into memory', 0ah, 0dh, 0

times 510-($-$$) db 0
dw 0xaa55