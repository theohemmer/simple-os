#include "kernel/lib/include/stdio.h"

#include <stdarg.h>

typedef struct printer_struct_t {
    char specifier;
    int (*fct)(va_list *args);
} printer_struct;

static int put_nbr_va(va_list *args)
{
    return (put_nbr(va_arg(*args, int)));
}

static int putstr_va(va_list *args)
{
    return (puts(va_arg(*args, char *)));
}

static int putchar_va(va_list *args)
{
    return (putchar(va_arg(*args, int)));
}

static int putnbr_hex_va(va_list *args)
{
    return (putnbr_base(va_arg(*args, int), "0123456789ABCDEF"));
}

static int putnbr_oct_va(va_list *args)
{
    return (putnbr_base(va_arg(*args, int), "01234567"));
}

static int put_addr_hex(va_list *args)
{
    puts("0x");
    return (put_unsigned_long_base(va_arg(*args, unsigned long), "0123456789abcdef") + 2);
}

static int put_unsigned_nbr_va(va_list *args)
{
    return (put_unsigned_nbr(va_arg(*args, unsigned int)));
}

static int put_unsigned_oct_va(va_list *args)
{
    return (put_unsigned_nbr_base(va_arg(*args, unsigned int), "01234567"));
}

static int put_unsigned_hex_min_va(va_list *args)
{
    return (put_unsigned_nbr_base(va_arg(*args, unsigned int), "0123456789abcdef"));
}

static int put_unsigned_hex_maj_va(va_list *args)
{
    return (put_unsigned_nbr_base(va_arg(*args, unsigned int), "0123456789ABCDEF"));
}

static int print_percent(va_list *args)
{
    (void)(args);
    putchar('%');
    return (1);
}

static int put_unsigned_bin_va(va_list *args)
{
    return (put_unsigned_nbr_base(va_arg(*args, unsigned int), "01"));
}

static int showstr_va(va_list *args)
{
    return (showstr(va_arg(*args, char *)));
}

static const printer_struct specifier[] = {
    {'d', put_nbr_va},
    {'i', put_nbr_va},
    {'u', put_unsigned_nbr_va},
    {'o', put_unsigned_oct_va},
    {'x', put_unsigned_hex_min_va},
    {'X', put_unsigned_hex_maj_va},
    {'s', putstr_va},
    {'c', putchar_va},
    {'p', put_addr_hex},
    {'b', put_unsigned_bin_va},
    {'S', showstr_va},
    {'%', print_percent}
};

static int printf_parser(char const *format, va_list *args, int *written)
{
    int i = 0;

    for (i = 0; i <= 11; i++)
        if (format[0] == specifier[i].specifier)
            break;
    if (i == 11 && format[0] != specifier[i].specifier)
        i = 12;
    if (i <= 11 && i >= 0) {
        *written = *written + specifier[i].fct(args);
    }
    else {
        putchar('%');
        putchar(format[0]);
        *written = *written + 2;
    }
    return (1);
}

static int printf_launch(char const *format, va_list *args)
{
    int written = 0;

    for (int i = 0; format[i]; i++) {
        if (format[i] == '%')
            i += printf_parser(format + i + 1, args, &written);
        else {
            putchar(format[i]);
            written++;
        }
    }
    return (written);
}

int printf(char const *format, ...)
{
    va_list args;
    int written = 0;

    va_start(args, format);
    printf_launch(format, &args);    
    va_end(args);
    return (written);
}