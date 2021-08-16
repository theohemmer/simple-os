#include "driver/port.h"
#include "driver/pic.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/stdlib.h"

void pic_send_eio(unsigned char irq)
{
    if (irq >= 8)
        port_byte_out(SPIC_COMMAND, 0x20);
    port_byte_out(MPIC_COMMAND, 0x20);
}

void pic_mask_irq(unsigned char irq)
{
    if (irq >= 8) {
        port_byte_out(SPIC_DATA, port_byte_in(SPIC_DATA) | (1 << (irq - 8)));
    } else {
        port_byte_out(MPIC_DATA, port_byte_in(MPIC_DATA) | (1 << irq));
    }
}

void pic_unmask_irq(unsigned char irq)
{
    if (irq >= 8) {
        port_byte_out(SPIC_DATA, port_byte_in(SPIC_DATA) & ~(1 << (irq - 8)));
    } else {
        port_byte_out(MPIC_DATA, port_byte_in(MPIC_DATA) & ~(1 << irq));
    }
}

void pic_remap(unsigned int offset1, unsigned int offset2)
{
    unsigned char mask_master, mask_slave;

    if (offset1 % 8 != 0 || offset2 % 8 != 0) {
        printf("Trying to remap the pic with non divisible by 8 offsets");
        abort();
    }
    mask_master = port_byte_in(MPIC_DATA);
    mask_slave = port_byte_in(SPIC_DATA);

    port_byte_out(MPIC_COMMAND, 0x10 | 0x01);
    port_byte_out(SPIC_COMMAND, 0x10 | 0x01);

    port_byte_out(MPIC_DATA, offset1);
    port_byte_out(SPIC_DATA, offset2);

    port_byte_out(MPIC_DATA, 0x4);
    port_byte_out(SPIC_DATA, 0x2);

    port_byte_out(MPIC_DATA, 0x01);
    port_byte_out(SPIC_DATA, 0x01);

    port_byte_out(MPIC_DATA, mask_master);
    port_byte_out(SPIC_DATA, mask_slave);
}

void pic_first_init(void)
{
    pic_remap(0x20, 0x28);
    port_byte_out(MPIC_DATA, 0xff); // Ignore all IRQs on master
    port_byte_out(SPIC_DATA, 0xff); // Ignore all IRQs on slave
}