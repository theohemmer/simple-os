#include "kernel/lib/include/stdio.h"

void abort(void)
{
    puts("abort(): Aborted.\n");
    while (1);
}