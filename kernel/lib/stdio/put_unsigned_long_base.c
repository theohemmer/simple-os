#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

int convert_unsigned_long(unsigned long nbr, int bs, char const *base)
{
    int res = 0;

    if (nbr / bs == 0) {
        putchar(base[nbr % bs]);
        return (1);
    }
    res += convert_unsigned_long(nbr / bs, bs, base);
    putchar(base[(nbr % bs)]);
    return (res + 1);
}

int put_unsigned_long_base(unsigned long nbr, char const *base)
{
    int base_size = strlen(base);

    return (convert_unsigned_long(nbr, base_size, base));
}
