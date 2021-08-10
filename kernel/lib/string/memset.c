#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
    unsigned char *dest = s;

    while(n-- > 0)
        *dest++ = c;
    return (dest);
}