#ifndef H_PORT
#define H_PORT

unsigned char port_byte_in(unsigned short port);
unsigned short port_word_in(unsigned short port);
unsigned int port_dword_in(unsigned short port);

void port_byte_out(unsigned short port, unsigned char data);
void port_word_out(unsigned short port, unsigned short data);
void port_dword_out(unsigned short port, unsigned int data);

#endif