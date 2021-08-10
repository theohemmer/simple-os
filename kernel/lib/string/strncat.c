#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

char *strncat(char *dest, char const *src, int n)
{
    int len = strlen(dest);
    int i;

    for (i = 0; src[i] != '\0' && i < n; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return (dest);
}
