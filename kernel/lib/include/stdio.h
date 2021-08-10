#ifndef H_STDIO
#define H_STDIO

int printf(const char *format, ...);
int putchar(char c);
int puts(const char *s);
int put_nbr(int nb);
int printf(char const *format, ...);
int str_showstr(char const *str);
int showmem(char const *str, int size);
int putnbr_base(int nbr, char const *base);
int put_unsigned_long_base(unsigned long nbr, char const *base);
int put_unsigned_nbr_base(unsigned int nbr, char const *base);
int put_unsigned_nbr(unsigned int nbr);
int showstr(char const *str);

#endif