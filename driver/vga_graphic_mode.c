#include <stddef.h>
#include "driver/vga_graphic_mode.h"
#include "driver/port.h"

unsigned char *enable_graphic_256_xmode()
{
    port_byte_out(0x3ce, 0x06);
    port_byte_out(0x3cf, 0b0011); // Miscellaneous Graphic Register, Select 256K Memory map
    port_byte_out(0x3ce, 0x05);
    port_byte_out(0x3cf, 0b01000000); // Graphics Mode Register, enable 256 colors mode */
    port_byte_out(0x3ce, 0x03);
    port_byte_out(0x3cf, 0b00000000); // Data Rotate register, Don't rotate data */
    port_byte_out(0x3c4, 0x01);
    port_byte_out(0x3c5, 0x1); // Switch to 8 Dot Modes (360x320 pixels)
    port_byte_out(0x3c4, 0x02);
    port_byte_out(0x3c5, 0b11111); // Map Mask Register: Enable Read from all Memory Plane
    port_byte_out(0x3c4, 0x04);
    port_byte_out(0x3c5, 0b0110); // Disable Chain 4, enable Extended Memory
    port_byte_out(0x3d4, 0x09);
    port_byte_out(0x3d5, 0x41); // Max Scan Line: Set Max Scan Line To 0 and Enable Scan Doubling
    port_byte_out(0x3d4, 0x0a);
    port_byte_out(0x3d5, 0x0); // Disable Cursor
    port_byte_out(0x3ce, 0x08);
    port_byte_out(0x3cf, 0xff); // Bit Mask for Write mode, enable all bits
    port_byte_out(0x3d4, 0x14);
    port_byte_out(0x3d5, 0x0); // Disable long mod
    port_byte_out(0x3d4, 0x17);
    port_byte_out(0x3d5, 0xe3); // Enable word mode
    port_byte_out(0x3c2, 0x65);

    return ((unsigned char *) VGA_FRONT_BUFFER);
}


unsigned char *switch_buffers()
{
    static unsigned char *visible_buffer = (unsigned char *) VGA_FRONT_BUFFER;
    static unsigned char *non_visible_buffer = (unsigned char *) VGA_BACK_BUFFER;
    unsigned char *tmp = visible_buffer;
    unsigned int new_addr;

    visible_buffer = non_visible_buffer;
    non_visible_buffer = tmp;

    new_addr = (unsigned int) visible_buffer & 0x0FFFF;

    __asm__ volatile("cli");
    while (port_byte_in(0x3da) & 0b00001000);
    port_byte_out(0x3d4, 0x0c);
    port_byte_out(0x3d5, (new_addr >> 8));
    port_byte_out(0x3d4, 0x0d);
    port_byte_out(0x3d5, (new_addr & 0xff));
    while (!(port_byte_in(0x3da) & 0b00001000));
    __asm__ volatile("sti");

    return (non_visible_buffer);
}

/*
    Explication:
    N'importe quelle nombre pour X finiras par 0, 1, 2 ou 3 en binaire (un peu comme un modulo 4)
    Donc on & ce nombre avec 3 pour récupérer uniquement les deux derniers bits (comme un modulo 4)
    Les 2 derniers bits servent a shit le nombre 1 vers la droite pour selection le plan ou on va ecrire

    40 = 10 1000 & 3 = 0000 = 0. 1 << 0 = 0001
    41 = 10 1001 & 3 = 0001 = 1. 1 << 1 = 0010
    42 = 10 1010 & 3 = 0010 = 2. 1 << 2 = 0100
    43 = 10 1011 & 3 = 0011 = 3. 1 << 3 = 1000
*/
void put_a_pixel(int x, int y, int color, unsigned char *buffer)
{
    port_byte_out(0x3c4, 0x02);
    port_byte_out(0x3c5, 1 << (x&3)); // voir example
    buffer[((320*y)+x)/4] = color;
}

void add_color_to_dac(unsigned char r, unsigned char g, unsigned char b, unsigned char index)
{
    static int previous_index = -2;

    if (previous_index + 1 != index)
        port_byte_out(0x3c8, index);
    port_byte_out(0x3c9, r);
    port_byte_out(0x3c9, g);
    port_byte_out(0x3c9, b);
    previous_index = index;
}