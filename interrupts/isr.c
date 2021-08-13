#include "interrupts/idt.h"
#include "interrupts/isr.h"

void registers_isr(void)
{
    printf("This should print\n\r");
    register_an_interrupt(0, (unsigned int) isr0);
    register_an_interrupt(1, (unsigned int) isr1);
    register_an_interrupt(2, (unsigned int) isr2);
    register_an_interrupt(3, (unsigned int) isr3);
    register_an_interrupt(4, (unsigned int) isr4);
    register_an_interrupt(5, (unsigned int) isr5);
    register_an_interrupt(6, (unsigned int) isr6);
    register_an_interrupt(7, (unsigned int) isr7);
    register_an_interrupt(8, (unsigned int) isr8);
    register_an_interrupt(9, (unsigned int) isr9);
    register_an_interrupt(10, (unsigned int) isr10);
    register_an_interrupt(11, (unsigned int) isr11);
    register_an_interrupt(12, (unsigned int) isr12);
    register_an_interrupt(13, (unsigned int) isr13);
    register_an_interrupt(14, (unsigned int) isr14);
    register_an_interrupt(15, (unsigned int) isr15);
    register_an_interrupt(16, (unsigned int) isr16);
    register_an_interrupt(17, (unsigned int) isr17);
    register_an_interrupt(18, (unsigned int) isr18);
    register_an_interrupt(19, (unsigned int) isr19);
    register_an_interrupt(20, (unsigned int) isr20);
    register_an_interrupt(21, (unsigned int) isr21);
    register_an_interrupt(22, (unsigned int) isr22);
    register_an_interrupt(23, (unsigned int) isr23);
    register_an_interrupt(24, (unsigned int) isr24);
    register_an_interrupt(25, (unsigned int) isr25);
    register_an_interrupt(26, (unsigned int) isr26);
    register_an_interrupt(27, (unsigned int) isr27);
    register_an_interrupt(28, (unsigned int) isr28);
    register_an_interrupt(29, (unsigned int) isr29);
    register_an_interrupt(30, (unsigned int) isr30);
    register_an_interrupt(31, (unsigned int) isr31);

    register_the_idt();
    printf("This should print too\n\r");
}

void isr_handler(reg_t *test)
{
    printf("Called %d %x\n\r", test->code, test->error);
}