#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

int convert_unsigned(unsigned int nbr, int base_size, char const *base)
{
    int res = 0;

    if (nbr / base_size == 0) {
        putchar(base[nbr % base_size]);
        return (1);
    }
    res += convert_unsigned(nbr / base_size, base_size, base);
    putchar(base[(nbr % base_size)]);
    return (res + 1);
}

int put_unsigned_nbr_base(unsigned int nbr, char const *base)
{
    int base_size = strlen(base);

    if (nbr < 0x10)
        putchar('0');

    return (convert_unsigned(nbr, base_size, base));
}
