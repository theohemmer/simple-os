#include "driver/pic.h"
#include "driver/ps2.h"
#include "driver/port.h"
#include "kernel/lib/include/stdio.h"

unsigned int bit(int n)
{
    return 1 << n;
}

void ps2_write_command(unsigned char command)
{
    while (!port_byte_in(0x64) & bit(1));
    port_byte_out(0x64, command);
}

unsigned char ps2_read_data(unsigned char *timeout)
{
    unsigned int count = 100000;

    while (((port_byte_in(0x64) & bit(0)) != 1) && --count);
    if (count == 0) {
        //printf("READ TIMEOUT.\n\r");
        *timeout = 1;
        return (0);
    }
    return (port_byte_in(0x60));
}

unsigned char ps2_write_data(unsigned char data)
{
    while (!port_byte_in(0x64) & bit(1));
    port_byte_out(0x60, data);
}

void ps2_enable()
{
    unsigned char dont_care = 0;

    ps2_write_command(PS2_DISABLE_PORT_1);
    ps2_write_command(PS2_DISABLE_PORT_2);

    port_byte_in(0x60); // Flush output

    ps2_write_command(PS2_READ_CONFIG);
    unsigned char config = ps2_read_data(&dont_care); // Read the config

    ps2_write_command(PS2_SELF_TEST);
    unsigned char self_test = ps2_read_data(&dont_care); // Make a self test
    if (self_test != 0x55) {
        printf("Self test error.\n\r");
        return;
    }
    printf("Self test succeed.\n\r");

    ps2_write_command(PS2_WRITE_CONFIG);
    ps2_write_data(config); // Restor config after self test

    ps2_write_command(PS2_ENABLE_PORT_2);
    ps2_write_command(PS2_READ_CONFIG);
    unsigned char other_config = ps2_read_data(&dont_care); // Read config to check if Port2 is Supported
    if (other_config & bit(5)) {
        printf("Mouse not supported.\n\r");
        return;
    }
    printf("Mouse supported.\n\r");
    ps2_write_command(PS2_DISABLE_PORT_2); // Disable The Port 2 Again

    ps2_write_command(PS2_INTERFACE_TEST_PORT_1);
    if (ps2_read_data(&dont_care) != 0x0) {
        printf("PS2 Port 1 Interface check failed.\n\r");
        return;
    }
    printf("-> PS2 Port 1 Interface check succeed.\n\r");

    ps2_write_command(PS2_INTERFACE_TEST_PORT_2);
    if (ps2_read_data(&dont_care) != 0x0) {
        printf("PS2 Port 2 Interface check failed.\n\r");
        return;
    }
    printf("-> PS2 Port 2 Interface check succeed.\n\r");

    config |= bit(0); // Enable Interrupts on port 1
    config |= bit(1); // Enable Interrupts on port 2
    config &= 0b10111111;

    ps2_write_command(PS2_WRITE_CONFIG);
    ps2_write_data(config);

    ps2_write_command(PS2_ENABLE_PORT_1);
    ps2_write_command(PS2_ENABLE_PORT_2);

    unsigned char should_retry = 0;

    /*printf("Searching for Device Types.\n\r");


    ps2_write_command(PS2_WRITE_ON_PORT_2);
    ps2_write_data(0xF5);
    while (ps2_read_data() != 0xFA);
    ps2_write_command(PS2_WRITE_ON_PORT_2);
    ps2_write_data(0xF2);
    while (ps2_read_data() != 0xFA);
    while ((should_retry = ps2_read_data()) == 0xFA);
    port_one = ps2_read_data();

    printf("Device Type2: %x\n\r", should_retry);
    ps2_write_command(PS2_WRITE_ON_PORT_2);
    ps2_write_data(0xF4);
    while(ps2_read_data() != 0xFA);*/
}