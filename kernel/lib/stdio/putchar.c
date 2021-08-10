#include "driver/vga_text_mode.h"
#include "driver/port.h"

int putchar(char c)
{
    port_byte_out(0x3f8, c);
}