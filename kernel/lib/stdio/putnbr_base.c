#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

int convert(int nbr, int base_size, char const *base)
{
    int res = 0;
    if (nbr / base_size == 0) {
        putchar(base[nbr % base_size]);
        return (1);
    }
    res += convert(nbr / base_size, base_size, base);
    putchar(base[(nbr % base_size)]);
    return (res + 1);
}

int putnbr_base(int nbr, char const *base)
{
    int base_size = strlen(base);
    int neg = 0;

    if (nbr < 0) {
        nbr = -(nbr);
        putchar('-');
        neg++;
    }
    return (convert(nbr, base_size, base) + neg);
}
