#include "kernel/lib/include/stdio.h"

void print_hex_number(unsigned int addr, int size)
{
    char base_hexa[] = "0123456789ABCDEF";

    if (size == 0)
        return;
    print_hex_number(addr / 16, size - 1);
    putchar(base_hexa[addr % 16]);
}

void print_hex_chars(char const *str, int size, int pos)
{
    int i = 0;

    for (i = i; i < size && i < 16; i++) {
        print_hex_number(str[i + pos], 2);
        if (i % 2 == 1)
            putchar(' ');
    }
    for (int o = i * 2; o < 16 * 2; o++)
        putchar(' ');
    for (int o = i / 2; o < 8; o++)
        putchar(' ');
}

void print_all_chars(char const *str, int size, int pos)
{
    for (int i = 0; i < size && i < 16; i++) {
        if (str[i + pos] < 32 || str[i + pos] >= 127)
            putchar('.');
        else
            putchar(str[i + pos]);
    }
}

void print_dump(char const *str, int size, int base_size)
{
    unsigned int pos = base_size - size;
    unsigned long str_addr = (unsigned long) &str;

    if (size <= 0)
        return;
    print_hex_number(str_addr + pos, 8);
    putchar(':');
    putchar(' ');
    print_hex_chars(str, size, pos);
    print_all_chars(str, size, pos);
    putchar('\n');
    print_dump(str, size - 16, base_size);
}

int showmem(char const *str, int size)
{
    if (size < 0)
        return (0);
    print_dump(str, size, size);
    return (0);
}
