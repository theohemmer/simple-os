#include "driver/ps2.h"
#include "interrupts/irq.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/stdlib.h"
#include "kernel/command_queue.h"

command_queue_t *kb_command_queue = NULL;

void flush_keyboard_queue(void)
{
    if (kb_command_queue != NULL)
        ps2_write_data(kb_command_queue->command);
}

static int reset_keyboard(unsigned char received, int reset)
{
    static int state = 0;

    if (state == 0) {
        push_to_queue(&kb_command_queue, 0xFF, &reset_keyboard);
        state = 1;
        return (1);
    }
    if (state == 1) {
        if (received == 0xFA)
            return (0);
        if (received == 0xAA) {
            printf(" -- Keyboard self test succed.\n\r");
        } else {
            printf("Keyboard self test failed.\n\r");
        }
        pop_from_queue(&kb_command_queue);
        state = 0;
        return (1);
    }
    if (reset == 1) {
        pop_from_queue(&kb_command_queue);
        state = 0;
        return (0);
    }
    return (0);
}

static int get_device_id(unsigned char received, int rs)
{
    static int state = 0;
    int id = received;
    unsigned char reset = 0;

    if (state == 0) {
        push_to_queue(&kb_command_queue, 0xF5, &get_device_id);
        state = 1;
        return (1);
    }
    if (state == 1) {
        if (received == 0xFA) {
            pop_from_queue(&kb_command_queue);
            push_to_queue(&kb_command_queue, 0xF2, &get_device_id);
            state = 2;
            return (1);
        }
    }
    if (state == 2) {
        if (received == 0xFA)
            return (0);
        while (1) {
            id = (ps2_read_data(&reset) << 8) | id;
            if (reset == 1)
                break;
        }
        printf(" -- Keybord device type ID: %x\n\r", id);
        pop_from_queue(&kb_command_queue);
        push_to_queue(&kb_command_queue, 0xF4, &get_device_id);
        state = 3;
        return (1);
    }
    if (state == 3) {
        if (received == 0xFA) {
            state = 0;
            pop_from_queue(&kb_command_queue);
            return (0);
        }
    }
    if (reset == 1) {
        pop_from_queue(&kb_command_queue);
        state = 0;
        return (0);
    }
    return (0);
}

void keyboard_handler(void)
{
    unsigned char timeout = 0;
    unsigned char readed = ps2_read_data(&timeout);

    if (readed == 0xFE && kb_command_queue != NULL) {
        ps2_write_data(kb_command_queue->command);
        return;
    }
    if (kb_command_queue != NULL) {
        if (kb_command_queue->callback(readed, timeout) == 1)
            flush_keyboard_queue();
        return;
    }
}

void install_keyboard()
{
    // Port 1 and 2 have already been activated by the PS2 driver
    // Just need to install the IRQ handler, reset the keyboard
    // Set default config, and self-test it

    install_irq_handler(1, keyboard_handler);
    get_device_id(0, 0);
    reset_keyboard(0, 0);
}