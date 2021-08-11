[bits 16]

gdt_start:

; empty selector
gdt_null:
dd 0x0
dd 0x0

; base: 0x00
; limit: 0xF FF FC

; access byte:
; PRESENT          PRIVILEGE      DESCRIPTOR      EXECUTABLE
; 1 (mandatory)    00 (kernel)    1 (code/data)   1 (yes)
; DIRECTION        READ/WRIABLE   ACCESSED
; 0 (grows down)   1 (readable)   0 (useless)

; flags:
; GRANULARITY      SIZE                           USELESS
; 1 (4KiB pages)   1 (32bits protected mode)      11 (useless)
gdt_code:
dw 0xffff   ; limit: 0-15
dw 0x0      ; base: 0-15
db 0x0      ; base: 16-23
db 10011010b; acces bytes (8 bits)
db 11001111b; limit:51-48 (4 bits), flags (4 bits)
db 0x0      ; base: 24-31

; base: 0x00
; limit: 0xF FF FC

; access byte:
; PRESENT          PRIVILEGE      DESCRIPTOR      EXECUTABLE
; 1 (mandatory)    00 (kernel)    1 (code/data)   0 (no)
; DIRECTION        READ/WRIABLE   ACCESSED
; 0 (grows down)   1 (writable)   0 (useless)

; flags:
; GRANULARITY      SIZE                           USELESS
; 1 (4KiB pages)   1 (32bits protected mode)      11 (useless)
gdt_data:
dw 0xffff
dw 0x0
db 0x0
db 10010010b
db 11001111b
db 0x0

gdt_end:

gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start