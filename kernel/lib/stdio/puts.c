#include "driver/vga_text_mode.h"
#include "kernel/lib/include/string.h"
#include "kernel/lib/include/stdio.h"

int puts(const char *s)
{
    for (int i = 0; s[i]; i++)
        putchar(s[i]);
    return (strlen(s));
}