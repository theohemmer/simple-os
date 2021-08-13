[bits 32]
[extern isr_handler]
[extern irq_handler]

%macro handler_macro 2
    handle_%+%1:
        pushad

        mov ax, ds
        push eax    ; save data segment

        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov gs, ax
        mov fs, ax  ; set data segments

        push esp
        call %2
        pop eax     ; pop the ESP pushed before the call

        pop eax
        mov ds, ax
        mov es, ax
        mov gs, ax
        mov fs, ax  ; restore data segments

        popad

        add esp, 8  ; Remove the 2 params that's left in the stack
        sti         ; reenable interrupts
        iret
%endmacro

%macro isr_macro 1-2
    global isr%+%1
    isr%+%1:
        cli
        %if %0 = 1
            push byte 0x0
            push byte %1
        %else
            push byte %2
            push byte %1
        %endif
        jmp handle_isr
%endmacro

%macro irq_macro 2
    global irq%+%1
    irq%+%1:
        cli
        push byte %2
        push byte %1
        jmp handle_irq
%endmacro

handler_macro isr, isr_handler
handler_macro irq, irq_handler

isr_macro 0, 0  ; Divide By 0
isr_macro 1, 0  ; Debug
isr_macro 2, 0  ; Non-Maskable Interrupt
isr_macro 3, 0  ; Breakpoint
isr_macro 4, 0  ; Overflow
isr_macro 5, 0  ; Bound Range Exceeded
isr_macro 6, 0  ; Invalid OpCode
isr_macro 7, 0  ; Device Not Available
isr_macro 8     ; Double Fault
isr_macro 9, 0  ; Coprocessor Segment Overrun
isr_macro 10    ; Invalid TTS
isr_macro 11    ; Segment Not Present
isr_macro 12    ; Stack-Segment Fault
isr_macro 13    ; General Protection Fault
isr_macro 14    ; Page Fault
isr_macro 15, 0 ; Reserved
isr_macro 16, 0 ; x87 Floating-Point Exception
isr_macro 17    ; Alignment Check
isr_macro 18, 0 ; Machine Check
isr_macro 19, 0 ; SIMD Floating-Point Exception
isr_macro 20, 0 ; Virtualization Exception
isr_macro 21, 0 ; Reserved
isr_macro 22, 0 ; Reserved
isr_macro 23, 0 ; Reserved
isr_macro 24, 0 ; Reserved
isr_macro 25, 0 ; Reserved
isr_macro 26, 0 ; Reserved
isr_macro 27, 0 ; Reserved
isr_macro 28, 0 ; Reserved
isr_macro 29, 0 ; Reserved
isr_macro 30, 0 ; Security Exception
isr_macro 31, 0 ; Reserved

irq_macro 0, 0  ; Progammable Interrupt Timer Interrupt
irq_macro 1, 0  ; Keyboard Interrupt
irq_macro 2, 0  ; Cascade
irq_macro 3, 0  ; COM2
irq_macro 4, 0  ; COM1
irq_macro 5, 0  ; LPT2
irq_macro 6, 0  ; Floppy Disk
irq_macro 7, 0  ; LPT1 / Spurious Interrupt
irq_macro 8, 0  ; CMOS RTC
irq_macro 9, 0  ; Free for peripherals / NIC
irq_macro 10, 0 ; Free for peripherals / SCSI / NIC
irq_macro 11, 0 ; Free for peripherals / SCSI / NIC
irq_macro 12, 0 ; PS2 Mouse
irq_macro 13, 0 ; FPU / Coprocessor / Inter-processor
irq_macro 14, 0 ; Primary ATA Hard Disk
irq_macro 15, 0 ; Seconday ATA Hard Disk / Spurious Interrupt