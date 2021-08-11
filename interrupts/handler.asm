[bits 32]
[extern isr_handler]

handle_interrupt:
    ; TODO, THIS WILL CRASH
    iret

; Divide By 0
global isr0
isr0:
    cli
    push byte 0x0
    push byte 0
    jmp handle_interrupt

; Debug
global isr1
isr1:
    cli
    push byte 0x0
    push byte 1
    jmp handle_interrupt

; Non-Maskable Interrupt
global isr2
isr2:
    cli
    push byte 0x0
    push byte 2
    jmp handle_interrupt

; Breakpoint
global isr3
isr3:
    cli
    push byte 0x0
    push byte 3
    jmp handle_interrupt

; Overflow
global isr4
isr4:
    cli
    push byte 0x0
    push byte 4
    jmp handle_interrupt

; Bound Range Exceeded
global isr5
isr5:
    cli
    push byte 0x0
    push byte 5
    jmp handle_interrupt

; Invalid OpCode
global isr6
isr6:
    cli
    push byte 0x0
    push byte 6
    jmp handle_interrupt

; Device Not Available
global isr7
isr7:
    cli
    push byte 0x0
    push byte 7
    jmp handle_interrupt

; Double Fault
global isr8
isr8:
    cli
    ; Exception has an argument
    push byte 8
    jmp handle_interrupt

; Coprocessor Segment Overrun
global isr9
isr9:
    cli
    push byte 0x0
    push byte 9
    jmp handle_interrupt

; Invalid TTS
global isr10
isr10:
    cli
    ; Exception has an argument
    push byte 10
    jmp handle_interrupt

; Segment Not Present
global isr11
isr11:
    cli
    ; Exception has an argument
    push byte 11
    jmp handle_interrupt

; Stack-Segment Fault
global isr12
isr12:
    cli
    ; Exception has an argument
    push byte 12
    jmp handle_interrupt

; General Protection Fault
global isr13
isr13:
    cli
    ; Exception has an argument
    push byte 13
    jmp handle_interrupt

; Page Fault
global isr14
isr14:
    cli
    ; Exception has an argument
    push byte 14
    jmp handle_interrupt

; Reserved
global isr15
isr15:
    cli
    push byte 0x0
    push byte 15
    jmp handle_interrupt

; x87 Floating-Point Exception
global isr16
isr16:
    cli
    push byte 0x0
    push byte 16
    jmp handle_interrupt

; Alignment Check
global isr17
isr17:
    cli
    ; Exception has an argument
    push byte 17
    jmp handle_interrupt

; Machine Check
global isr18
isr18:
    cli
    push byte 0x0
    push byte 18
    jmp handle_interrupt

; SIMD Floating-Point Exception
global isr19
isr19:
    cli
    push byte 0x0
    push byte 19
    jmp handle_interrupt

; Virtualization Exception
global isr20
isr20:
    cli
    push byte 0x0
    push byte 20
    jmp handle_interrupt

; Reserved
global isr21
isr21:
    cli
    push byte 0x0
    push byte 21
    jmp handle_interrupt

; Reserved
global isr22
isr22:
    cli
    push byte 0x0
    push byte 22
    jmp handle_interrupt

; Reserved
global isr23
isr23:
    cli
    push byte 0x0
    push byte 23
    jmp handle_interrupt

; Reserved
global isr24
isr24:
    cli
    push byte 0x0
    push byte 24
    jmp handle_interrupt

; Reserved
global isr25
isr25:
    cli
    push byte 0x0
    push byte 25
    jmp handle_interrupt

; Reserved
global isr26
isr26:
    cli
    push byte 0x0
    push byte 26
    jmp handle_interrupt

; Reserved
global isr27
isr27:
    cli
    push byte 0x0
    push byte 27
    jmp handle_interrupt

; Reserved
global isr28
isr28:
    cli
    push byte 0x0
    push byte 28
    jmp handle_interrupt

; Reserved
global isr29
isr29:
    cli
    push byte 0x0
    push byte 29
    jmp handle_interrupt

; Security Exception
global isr30
isr30:
    cli
    push byte 0x0
    push byte 30
    jmp handle_interrupt

; Reserved
global isr31
isr31:
    cli
    push byte 0x0
    push byte 31
    jmp handle_interrupt