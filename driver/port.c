unsigned char port_byte_in(unsigned short port)
{
    unsigned char data;

    asm volatile(
        "in %%dx, %%al"
        : "=a" (data)
        : "d" (port)
    );
    return (data);
}

unsigned short port_word_in(unsigned short port)
{
    unsigned short data;

    asm volatile(
        "in %%dx, %%ax"
        : "=a" (data)
        : "d" (port)
    );
    return (data);
}

unsigned int port_dword_in(unsigned short port)
{
    unsigned int data;

    asm volatile(
        "in %%dx, %%eax"
        : "=a" (data)
        : "d" (port)
    );
    return (data);
}

void port_byte_out(unsigned short port, unsigned char data)
{
    asm volatile(
        "out %%al, %%dx"
        :: "a" (data), "d" (port)
    );
}

void port_word_out(unsigned short port, unsigned short data)
{
    asm volatile(
        "out %%ax, %%dx"
        :: "a" (data), "d" (port)
    );
}

void port_dword_out(unsigned short port, unsigned int data)
{
    asm volatile(
        "out %%eax, %%dx"
        :: "a" (data), "d" (port)
    );
}