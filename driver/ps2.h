#ifndef H_PS2
#define H_PS2

#define PS2_DISABLE_PORT_1 0xAD
#define PS2_DISABLE_PORT_2 0xA7
#define PS2_READ_CONFIG 0x20
#define PS2_SELF_TEST 0xAA
#define PS2_WRITE_CONFIG 0x60
#define PS2_ENABLE_PORT_1 0xAE
#define PS2_ENABLE_PORT_2 0xA8
#define PS2_INTERFACE_TEST_PORT_1 0xAB
#define PS2_INTERFACE_TEST_PORT_2 0xA9
#define PS2_WRITE_ON_PORT_2 0xD4

void ps2_write_command(unsigned char command);
unsigned char ps2_read_data(unsigned char *timeout);
unsigned char ps2_write_data(unsigned char data);

void ps2_enable();

#endif