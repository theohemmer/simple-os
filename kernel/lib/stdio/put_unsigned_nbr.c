#include "kernel/lib/include/stdio.h"

int print_unsigned_nbr(unsigned int nb)
{
    unsigned int unit = nb % 10;
    int res = 0;

    nb = nb / 10;
    if (nb != 0)
        res += print_unsigned_nbr(nb);
    putchar(unit + 48);
    return (res + 1);
}

int put_unsigned_nbr(unsigned int nb)
{
    if (nb == 0) {
        putchar('0');
        return (1);
    }
    return (print_unsigned_nbr(nb));
}
