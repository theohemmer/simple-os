#include "interrupts/idt.h"
#include "interrupts/irq.h"
#include "interrupts/isr.h"
#include "driver/pic.h"

void registers_irq(void)
{
    register_an_interrupt(0x20, (unsigned int) irq0);
    register_an_interrupt(0x21, (unsigned int) irq1);
    register_an_interrupt(0x22, (unsigned int) irq2);
    register_an_interrupt(0x23, (unsigned int) irq3);
    register_an_interrupt(0x24, (unsigned int) irq4);
    register_an_interrupt(0x25, (unsigned int) irq5);
    register_an_interrupt(0x26, (unsigned int) irq6);
    register_an_interrupt(0x27, (unsigned int) irq7);
    register_an_interrupt(0x28, (unsigned int) irq8);
    register_an_interrupt(0x29, (unsigned int) irq9);
    register_an_interrupt(0x2A, (unsigned int) irq10);
    register_an_interrupt(0x2B, (unsigned int) irq11);
    register_an_interrupt(0x2C, (unsigned int) irq12);
    register_an_interrupt(0x2D, (unsigned int) irq13);
    register_an_interrupt(0x2E, (unsigned int) irq14);
    register_an_interrupt(0x2F, (unsigned int) irq15);
}

void irq_handler(reg_t *test)
{
    printf("IRQ Called %d %x\n\r", test->code, test->error);

    pic_send_eio(test->code);
}