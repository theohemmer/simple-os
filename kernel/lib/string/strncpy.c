char *strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    if (n < 0)
        return ("");
    for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}
