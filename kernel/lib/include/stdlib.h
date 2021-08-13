#ifndef H_STDLIB
#define H_STDLIB

#include <stddef.h>

__attribute__((__noreturn__))
void abort(void);

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif