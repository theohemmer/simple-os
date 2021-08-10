#include "driver/vga_text_mode.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"
#include <stddef.h>
#include <stdint.h>
#include "driver/port.h"

void print_offset()
{
    port_byte_out(0x3d4, 0x0e);
    unsigned int offeset = port_byte_in(0x3d5) << 8;
    port_byte_out(0x3d4, 0x0f);
    offeset = offeset | port_byte_in(0x3d5);
    printf("\r%d             ", offeset);
}

void set_offset(int offset)
{
    port_byte_out(0x3d4, 0x0e);
    port_byte_out(0x3d5, offset >> 8);
    port_byte_out(0x3d4, 0x0f);
    port_byte_out(0x3d5, offset & 0x00ff);
}
/*
0000 0000

0001 1111 // start
0001      // enabled

0123 4567 // bits
1111 1100 // attended result

0001 1111 << 3 = 1111 1000 = attended result 
(unsigned short) 0000 0001 << 2 = 0000 0100 = attended result

1111 1000 | 0000 0100 = 1111 1100 = RESULT
*/
void set_cursor_start(unsigned short start, unsigned short enabled)
{
    unsigned short to_write = start << 3;
    to_write |= (enabled << 2);
    to_write &= 0xfc; // 1111 1100, 6th and 7th bits are reserved, make sur to set them to 0

    port_byte_out(0x3d4, 0x0A);
    port_word_out(0x3d5, to_write);
}

void set_cursor_end(unsigned short end, unsigned char skew)
{
    unsigned short to_write = end << 3;
    to_write |= (skew << 1);
    to_write &= 0xfe; // 1111 1110, 7th bit is reserved, make sur to set it to 0

    port_byte_out(0x3d4, 0x0b);
    port_word_out(0x3d5, to_write);
}

void print_cursor_end()
{
    port_byte_out(0x3d4, 0x0b);
    unsigned short readed = port_word_in(0x3d5);

    unsigned short pos = (readed >> 3) & 0b00011111;
    unsigned short scew = (readed >> 1) & 0b00000011;
    printf("\rPos: %d  Scew: %d                           ", pos, scew);
}

void print_cursor_start()
{
    port_byte_out(0x3d4, 0x0A);
    unsigned short readed = port_word_in(0x3d5);

    unsigned short pos = (readed >> 3) & 0b00011111;
    unsigned short scew = (readed >> 2) & 0b00000001;
    printf("Pos: %d  On: %d     ", pos, scew);
}

void print_max_scan_line()
{
    port_byte_out(0x3d4, 0x09);
    unsigned short readed = port_word_in(0x3d5);
    printf("Max Scan Line Hex: %x\n", (unsigned short) readed);
    readed &= 0b00011111;

    printf("Max Scan Line: %d\n", readed);
}

void set_max_scan_line(unsigned short max_scan_line)
{
    port_byte_out(0x3d4, 0x09);
    unsigned short readed = port_byte_in(0x3d5);

    readed &= 0b11100000;
    max_scan_line &= 0b00011111;
    unsigned short to_write = readed | max_scan_line;

    port_byte_out(0x3d4, 0x09);
    port_byte_out(0x3d5, to_write);
}

void enable_graphic_256_xmode()
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
}

void drawline(int x0, int y0, int x1, int y1)
{
    int dx, dy, p, x, y;
    unsigned char *addr = 0xA0000;

    dx=x1-x0;
    if (y0 < y1)
        dy=y1-y0;
    else
        dy=y0-y1;

    x=x0;
    y=y0;

    p=2*dy-dx;

    while(x<x1) {
        if(p>=0) {
            put_a_pixel(x, y, 0x04, addr);
            if (y0 < y1)
                y++;
            else
                y--;
            p=p+2*dy-2*dx;
        } else {
            put_a_pixel(x, y, 0x04, addr);
            p=p+2*dy;
        }
        x=x+1;
    }
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

/*
unsigned char g_mode[] =
{
/* MISC */
/* Diff: Mhz dans la clock */
  /*  0x67*,
/* SEQ */
    /*0x03, 0x01, 0x0F, 0x00, 0x06, 
/* CRTC */
/* Diff: 0x55: Start Horizontal Retrace,     0x81: End Horizontal Retrace
         0x0E: Cursor End Register           0x03: Cursor Location High Register
         0x20: Cursor Location Low Register  0x8E: Vertical Retrace End Register
         0xE3: Mode Control Register*/
    /*0x5F, 0x4F, 0x50, 0x82, 0x55*, 0x81*, 0xBF, 0x1F,
    0x00, 0x41, 0x00, 0x0E*, 0x00, 0x00, 0x03*, 0x20*,
    0x9C, 0x8E*, 0x8F, 0x28, 0x00, 0x96, 0xB9, 0xE3*,
    0xFF, 
/* GC */
/* Diff: Miscellaneous Graphics Register */
    /*0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x03*, 0x0F,
    0xFF, 
/* AC */

    /*0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x14*, 0x07,
    0x38*, 0x39*, 0x3A*, 0x3B*, 0x3C*, 0x3D*, 0x3E*, 0x3F*,
    0x0C*, 0x00, 0x0F, 0x08*, 0x00, 
};*/

void main() {
    //port_byte_out(0x3c4, 0x02);
    //printf("\n%x", port_byte_in(0x3c5));
    //set_max_scan_line(0);
    port_byte_out(0x70, 0x00);
    int time1 = port_byte_in(0x71);
    int time2 = 0;
    int frame_counter = 0;
    enable_graphic_256_xmode();

    unsigned char *fronbuffer = 0xA0000;
    unsigned char *backbuffer = 0xAFFFF;

    char *tmp = fronbuffer;
    char *new_addr;
    unsigned char addr_high;
    unsigned char addr_low;

    int bg_color = 0x0f;
    int fg_color = 0x00;

    while((time2 = port_byte_in(0x71)) == time1);

    while (1) {
        /*for (int i = 0; i < 320; i++)
            addr[i] = 0x0f;
        for (int i = 0; i < 320 * 200; i+=320)
            addr[i] = 0x0f;
        for (int i = 320 - 1; i < 320 * 200; i+= 320)
            addr[i] = 0x0f;
        for (int i = 320 * 200 - 320; i < 320 * 200; i++) {
            for (int x = 0; x < 10000000; x++);
            addr[i] = 0x0f;
        }*/
        /*drawline(0, 0, 320, 200);
        drawline(0, 200, 320, 0);
        */
        for (int y = 0; y < 200; y++) {
            for (int x = 0; x < 320; x++) {
                fg_color = 0x00;
                bg_color = 0x0f;
                if (backbuffer == 0xA0000) {
                    bg_color = 0x00;
                    fg_color = 0x0f;
                }
                if (y == 0)
                    put_a_pixel(x, y, bg_color, backbuffer);
                else if (x == 0)
                    put_a_pixel(x, y, bg_color, backbuffer);
                else if (x == 319)
                    put_a_pixel(x, y, bg_color, backbuffer);
                else if (y == 199)
                    put_a_pixel(x, y, bg_color, backbuffer);
                else
                    put_a_pixel(x, y, 0x00, backbuffer);
            }
        }
        tmp = fronbuffer;
        fronbuffer = backbuffer;
        backbuffer = tmp;
        new_addr = (unsigned int) fronbuffer & 0x0FFFF;
        addr_high = ((unsigned int) new_addr) >> 8;
        addr_low = ((unsigned int) new_addr) & 0xff;
        // __asm__ volatile("cli"); TODO : Disable interrupts here before switching buffer
        while (port_byte_in(0x3da) & 0b00001000);
        port_byte_out(0x3d4, 0x0c);
        port_byte_out(0x3d5, addr_high);
        port_byte_out(0x3d4, 0x0d);
        port_byte_out(0x3d5, addr_low);
        while (!(port_byte_in(0x3da) & 0b00001000));
        frame_counter++;
        // __asm__ volatile("sti"); TODO: Re-Enable Interrupts here after switching buffer
        if ((time1 = port_byte_in(0x71)) != time2) {
            time2 = time1;
            printf("%d FPS\n\r", frame_counter);
            frame_counter = 0;
        }
    }
    /*

    for (int i = 0; i < 0xFFFF; i++) {
        int r = (i / 320) % 2;
        addr[i] = 1 + r;
    }

    //set_miscellaneous();

    /*for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            put_char_on_screen(' ' , x, y);
        }
    }
    set_miscellaneous();
    set_max_scan_line(0);
    print_max_scan_line();
    print_offset();
    print_cursor_end();
    print_cursor_start();
    for (int i = 0; i < 2; i++) {
        print_cursor_end();
        print_cursor_start();
        for (int i = 0; i++ < 700000000;);
    }
    set_cursor_start(0, 0);
    set_cursor_end(31, 0);
    print_cursor_end();
    print_cursor_start();
    for (int y = 0; y < 800; y++) {
        set_offset(y);
        for (int i = 0; i++ < 5000000;);
    }*/
}