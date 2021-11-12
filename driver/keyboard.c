#include "driver/ps2.h"
#include "interrupts/irq.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/stdlib.h"
#include "kernel/command_queue.h"
#include "driver/keyboard.h"

command_queue_t *kb_command_queue = NULL;

void flush_keyboard_queue(void)
{
    if (kb_command_queue != NULL) {
        printf("Flushing queue. %x\n", kb_command_queue->command);
        ps2_write_data(kb_command_queue->command);
    }
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

static int get_kb_scan_code(unsigned char received, int rs)
{
    static int state = 0;

    printf("Sate: %d Received: %x\n", state, received);
    if (state == 0) {
        state = 1;
        push_to_queue(&kb_command_queue, 0xF0, &get_kb_scan_code);
        return (1);
    }
    if (state == 1 || state == 2) {
        if (received == 0xFA && state == 1) {
            state = 2;
            pop_from_queue(&kb_command_queue);
            push_to_queue(&kb_command_queue, 0x00, &get_kb_scan_code);
            return (1);
        }
        if (received == 0xFA)
            return (0);
        printf("Scan Code: 0x%x\n\r", received);
        pop_from_queue(&kb_command_queue);
        state = 0;
        return (0);
    }
    if (rs == 1) {
        state = 0;
        pop_from_queue(&kb_command_queue);
        return (0);
    }
    return (0);
}

static int set_kb_scan_code(unsigned char received, int rs)
{
    static int state = 0;

    printf("Sate: %d Received: %x\n", state, received);
    if (state == 0) {
        state = 1;
        push_to_queue(&kb_command_queue, 0xF0, &set_kb_scan_code);
        return (1);
    }
    if (state == 1 || state == 2) {
        if (received == 0xFA && state == 1) {
            state = 2;
            pop_from_queue(&kb_command_queue);
            push_to_queue(&kb_command_queue, 0x02, &set_kb_scan_code);
            return (1);
        }
        if (received == 0xFA && state != 2)
            return (0);
        printf("Scan Code: 0x%x\n\r", received);
        pop_from_queue(&kb_command_queue);
        state = 0;
        return (0);
    }
    if (rs == 1) {
        state = 0;
        pop_from_queue(&kb_command_queue);
        return (0);
    }
    return (0);
}

key_t *last_char = &azerty_fr[UNKNOW_KEY];

void keyboard_handler(void)
{
    unsigned char timeout = 0;
    unsigned char readed = ps2_read_data(&timeout);
    unsigned int keycode = readed;

    if (readed == 0xFE && kb_command_queue != NULL) {
        ps2_write_data(kb_command_queue->command);
        return;
    }
    if (kb_command_queue != NULL) {
        if (kb_command_queue->callback(readed, timeout) == 1)
            flush_keyboard_queue();
        return;
    }
    if (readed != 0xe0 && readed != 0xe1 && readed != 0xf0 && readed != 0x00) {
        printf("Pressed: %s\n", azerty_fr[scan_code_to_key_nbr[readed]].name);
        azerty_fr[scan_code_to_key_nbr[readed]].is_pressed = 1;
        last_char = azerty_fr[scan_code_to_key_nbr[readed]].aff_min ? &azerty_fr[scan_code_to_key_nbr[readed]] : last_char;
    } else if (readed == 0xf0) {
        readed = ps2_read_data(&timeout);
        azerty_fr[scan_code_to_key_nbr[readed]].is_pressed = 0;
    } else if (readed == 0xe0) {
        readed = ps2_read_data(&timeout);
        if (readed == 0xf0) {
            readed = ps2_read_data(&timeout);
            if (readed == 0x7c) {
                keycode = readed;
                readed = ps2_read_data(&timeout);
                if (timeout && keycode != 0x0) // This condition check if there is a timeout, if there is a timeout so it cannot be the impr ecran key
                    azerty_fr[scan_code_e0_to_key_nbr[keycode]].is_pressed = 0;
                // Check for impr ecran key code
                else if (readed == 0xe0 && ps2_read_data(&timeout) == 0xf0 && ps2_read_data(&timeout) == 0x12 && !timeout)
                    azerty_fr[39 - 19].is_pressed = 0;
            } else if (readed != 0x0)
                azerty_fr[scan_code_e0_to_key_nbr[readed]].is_pressed = 0;
        } else if (readed != 0x0) {
            if (readed == 0x12) {
                keycode = readed;
                readed = ps2_read_data(&timeout);
                if (timeout && keycode != 0x0) {
                    azerty_fr[scan_code_e0_to_key_nbr[keycode]].is_pressed = 1;
                    last_char = azerty_fr[scan_code_e0_to_key_nbr[keycode]].aff_min ? &azerty_fr[scan_code_e0_to_key_nbr[keycode]] : last_char;
                }
                else if (readed == 0xe0 && ps2_read_data(&timeout) == 0x7c && !timeout)
                    azerty_fr[39 - 19].is_pressed = 1;
            } else if (readed != 0x0) {
                azerty_fr[scan_code_e0_to_key_nbr[readed]].is_pressed = 1;
                last_char = azerty_fr[scan_code_e0_to_key_nbr[readed]].aff_min ? &azerty_fr[scan_code_e0_to_key_nbr[readed]] : last_char;
            }
        }
    } else {
        for (int looped = 0, is_pause = 0; 1; looped++) {
            //printf("%x", readed);
            keycode <<= 8;
            readed = ps2_read_data(&timeout);
            keycode |= readed;
            if (timeout == 1)
                break;
            if (looped == 2 && keycode == 0xe11477e1) {
                keycode = 0;
                is_pause = 1;
            }
            if (looped == 6 && keycode == 0xf014f077 && is_pause == 1) {
                keycode = 0;
                is_pause = 0;
                azerty_fr[39-19].is_pressed = 1;
                //printf("%s PRESSED\n\r", azerty_fr[38 - 19].name);
            }
        }
        keycode >>= 8;
    }
}

unsigned char is_shifted()
{
    if (azerty_fr[74].is_pressed)
        return 1;
    if (azerty_fr[86].is_pressed)
        return 1;
    printf("Not shifted.\n");
    return 0;
}

unsigned char is_alted()
{
    if (azerty_fr[91].is_pressed && azerty_fr[94].is_pressed)
        return 1;
    if (azerty_fr[96].is_pressed)
        return 1;
    return 0;
}

key_t *getch()
{
    key_t *to_ret = &azerty_fr[UNKNOW_KEY];
    size_t count = 1000;

    while (last_char == &azerty_fr[UNKNOW_KEY] && count-- > 1);
    if (count == 0)
        return (to_ret);
    to_ret = last_char;
    last_char = &azerty_fr[UNKNOW_KEY];
    return (to_ret);
}

void install_keyboard()
{
    // Port 1 and 2 have already been activated by the PS2 driver
    // Just need to install the IRQ handler, reset the keyboard
    // Set default config, and self-test it

    install_irq_handler(1, keyboard_handler);
    get_kb_scan_code(0, 0);
    //set_kb_scan_code(0, 0);
    get_device_id(0, 0);
    reset_keyboard(0, 0);
    //get_kb_scan_code(0, 0)
}