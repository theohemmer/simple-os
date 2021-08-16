#include "driver/ps2.h"
#include "interrupts/irq.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/stdlib.h"

unsigned char act_command = 0x0;
unsigned char keyboard_state = 0;

typedef struct command_queue_s {
    unsigned char command;
    void (*callback)(unsigned char received, int reset);
    struct command_queue_s *next;
} command_queue_t;

command_queue_t *command_queue = NULL;

static void add_to_queue(command_queue_t **queue, unsigned char command, void (*callback)(unsigned char received, int reset))
{
    command_queue_t *new_node = malloc(sizeof(command_queue_t));
    command_queue_t *act = *queue;

    new_node->callback = callback;
    new_node->command = command;
    new_node->next = NULL;
    if (*queue == NULL) {
        *queue = new_node;
        return;
    }
    while (act->next != NULL)
        act = act->next;
    act->next = new_node;
}

static void pop_from_queue(command_queue_t **queue)
{
    command_queue_t *act = *queue;
    command_queue_t *prev = NULL;

    if ((*queue)->next == NULL) {
        free(*queue);
        *queue = NULL;
    }
    while (act->next != NULL) {
        prev = act;
        act = act->next;
    }
    free(act);
    prev->next = NULL;
}

static void flush_queue(command_queue_t *command_queue)
{
    if (command_queue != NULL) {
        ps2_write_data(command_queue->command);
    }
}

static void reset_keyboard(unsigned char received, int reset)
{
    static int state = 0;

    if (state == 0) {
        add_to_queue(&command_queue, 0xFF, &reset_keyboard);
        state = 1;
        return;
    }
    if (state == 1) {
        if (received == 0xFA)
            return;
        if (received == 0xAA) {
            printf("Keyboard self test succed.\n\r");
        } else {
            printf("Keyboard self test failed.\n\r");
        }
        pop_from_queue(&command_queue);
        state = 0;
    }
    if (reset == 1) {
        pop_from_queue(&command_queue);
        state = 0;
    }
}

static void get_device_id(unsigned char received, int rs)
{
    static int state = 0;
    int id = received;
    unsigned char reset = 0;

    if (state == 0) {
        add_to_queue(&command_queue, 0xF5, &get_device_id);
        state = 1;
        return;
    }
    if (state == 1) {
        if (received == 0xFA) {
            pop_from_queue(&command_queue);
            add_to_queue(&command_queue, 0xF2, &get_device_id);
            state = 2;
            flush_queue(command_queue);
            return;
        }
    }
    if (state == 2) {
        if (received == 0xFA) {
            printf("ACK :)\n\r");
            return;
        }
        while (1) {
            id = (ps2_read_data(&reset) << 8) | id;
            if (reset == 1) {
                break;
            }
        }
        printf("Device Type ID: %x\n\r", id);
        pop_from_queue(&command_queue);
        add_to_queue(&command_queue, 0xF4, &get_device_id);
        flush_queue(command_queue);
        state = 3;
    }
    if (state == 3) {
        if (received == 0xFA) {
            state = 0;
            pop_from_queue(&command_queue);
        }
    }
}

void keyboard_handler(void)
{
    unsigned char timeout = 0;
    unsigned char readed = ps2_read_data(&timeout);

    printf("Readed: %x\n\r", readed);
    if (readed == 0xFE) {
        ps2_write_data(act_command);
        return;
    }
    if (command_queue != NULL) {
        command_queue->callback(readed, timeout);
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
    flush_queue(command_queue);
}