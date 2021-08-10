#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"

char *strcat(char *dest, char const *src)
{
    int len = strlen(dest);
    int i;

    for (i = 0; src[i] != '\0'; i++)
        dest[len + i] = src[i];
    dest[len + i] = '\0';
    return (dest);
}
