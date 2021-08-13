#include "interrupts/idt.h"

idt_section_t idt[NUMBER_OF_INTERRUPTS] = {0};
idt_t idt_params = {0};

/*
                    1111 1111 1111 1111
0000 0000 0000 0000 0000 0000 0000 0000
1111 1111 1111 1111
*/
void register_an_interrupt(int n, unsigned int handler)
{
    idt[n].offset_low = (unsigned short) (handler & 0x0000ffff);
    idt[n].selector = 0x08;
    idt[n].zero = 0x00;
    idt[n].attributes = 0b10001110;
    idt[n].offset_high = (unsigned short) ((handler & 0xffff0000) >> 16);
}

void register_the_idt(void)
{
    idt_params.size = (sizeof(idt_section_t) * NUMBER_OF_INTERRUPTS) - 1;
    idt_params.addr = (unsigned int) &idt;
    __asm__ volatile("lidt %0" : : "m" (idt_params));
    __asm__ volatile("sti");
}