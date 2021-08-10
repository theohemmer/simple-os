#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *destc = dest;
    const unsigned char *srcc = src;

    while (n-- > 0) {
        *destc = *srcc;
        destc++;
        srcc++;
    }
    return (dest);
}