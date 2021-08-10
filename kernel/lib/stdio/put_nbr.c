#include "kernel/lib/include/stdio.h"

int print_nbr(int nb)
{
    int unit = nb % -10;
    int res = 0;

    nb = nb / -10;
    if (nb != 0)
        res = print_nbr(nb);
    if (unit < 0)
        putchar((-unit) + 48);
    else
        putchar(unit + 48);
    res++;
    return (res);
}

int put_nbr(int nb)
{
    int neg = 0;

    if (nb == 0) {
        putchar('0');
        return (1);
    }
    if (nb < 0) {
        putchar('-');
        neg++;
    }
    return (print_nbr(nb) + neg);
}
