#include <stddef.h>

void *memmove(void *dest, const void *src, size_t n)
{
    unsigned char *destc = dest;
    const unsigned char *srcc = src;

    if (dest < src) {
        while (n-- > 0) {
            *destc = *srcc;
            destc++;
            srcc++;
        }
    } else {
        destc = dest + (n - 1);
        srcc = src + (n - 1);
        while (n-- > 0)
            *destc-- = *srcc--;
    }
}