#include "kernel/lib/include/stdio.h"

int print_zeros(int nb)
{
    int res = 0;

    if (nb < 8) {
        res++;
        putchar(48);
    }
    if (nb >= 8 && nb != 127) {
        res++;
        putchar(48);
    }
    return (res);
}

int showstr(char const *str)
{
    int written = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < 32 || str[i] >= 127) {
            putchar('\\');
            written += print_zeros(str[i]);
            written += putnbr_base(str[i], "01234567") + 1;
        } else {
            putchar(str[i]);
            written++;
        }
    }
    return (written);
}
