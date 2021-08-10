#ifndef H_STRING
#define H_STRING

#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n);
void* memcpy(void *dest, const void *src, size_t n);
void* memmove(void *dest, const void *src, size_t n);
void* memset(void *s, int c, size_t n);
size_t strlen(const char *s);
int getnbr(char const *str);
char *strcpy(char *dest, char const *src);
char *strncpy(char *dest, char const *src, int n);
char *strstr(char *str, char const *to_find);
int strcmp(char const *s1, char const *s2);
int strncmp(char const *s1, char const *s2, int n);
char *strupcase(char *str);
char *strlowcase(char *str);
char *strcat(char *dest, char const *src);
char *strncat(char *dest, char const *src, int nb);

#endif