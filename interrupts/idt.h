#ifndef H_IDT
#define H_IDT

#define NUMBER_OF_INTERRUPTS 48

typedef struct {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char attributes;
    unsigned short offset_high;
} __attribute__((packed)) idt_section_t;

typedef struct {
    unsigned short size;
    unsigned int addr;
} __attribute__((packed)) idt_t;

void register_an_interrupt(int n, unsigned int handler);
void register_the_idt(void);

#endif