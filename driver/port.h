#ifndef H_PORT
#define H_PORT

/*!
    Read a byte on a port
    \param port the port that will be readed
*/
unsigned char port_byte_in(unsigned short port);

/*!
    Read a word on a port
    \param port the port that will be readed
*/
unsigned short port_word_in(unsigned short port);

/*!
    Read a double word on a port
    \param port the port that will be readed
*/
unsigned int port_dword_in(unsigned short port);

/*!
    Write a byte on a port
    \param port the port that will be writed
    \param data the data to write
*/
void port_byte_out(unsigned short port, unsigned char data);

/*!
    Write a word on a port
    \param port the port that will be writed
    \param data the data to write
*/
void port_word_out(unsigned short port, unsigned short data);

/*!
    Write a double word on a port
    \param port the port that will be writed
    \param data the data to write
*/
void port_dword_out(unsigned short port, unsigned int data);

#endif