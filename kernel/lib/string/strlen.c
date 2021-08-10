#include <stddef.h>

size_t strlen(const char *s)
{
    size_t idx = 0;

    while (s[++idx]);
    return (idx);
}