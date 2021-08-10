#include <stddef.h>
#include <stdint.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *ss1 = s1;
    const unsigned char *ss2 = s2;

    while (n-- > 0) {
        if (*ss1++ != *ss2++)
            return *ss1 - *ss2;
    }
    return (0);
}