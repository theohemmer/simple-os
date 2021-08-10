int strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (i = 0; s1[i] && s2[i]; i++)
        if (s1[i] != s2[i])
            return (0);
    if (s1[i] == s2[i])
        return (1);
    return (0);
}
