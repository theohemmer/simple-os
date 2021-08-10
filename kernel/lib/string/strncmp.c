#include "kernel/lib/include/stdio.h"

int strncmp(char const *s1, char const *s2, int n)
{
    if (n < 0)
        return (0);
    for (int i = 0; (s1[i] != '\0' || s2[i] != '\0') && i < n; i++)
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    return (0);
}
