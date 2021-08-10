#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"
#include <stddef.h>

char *strstr(char *str, char const *to_find)
{
    int len = strlen(to_find);

    if (len == 0)
        return ("");
    for (int i = 0, o = 0; str[i] != '\0'; i++) {
        if (str[i] == to_find[o])
            o++;
        else
            o = 0;
        if (o == len)
            return (str + (i - o) + 1);
    }
    return (NULL);
}
