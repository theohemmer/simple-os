#include "driver/ps2.h"
#include "interrupts/irq.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/stdlib.h"
#include "kernel/command_queue.h"
#include "driver/mouse.h"

command_queue_t *ms_command_queue = NULL;

void flush_mouse_queue(void)
{
    if (ms_command_queue != NULL) {
        ps2_write_command(PS2_WRITE_ON_PORT_2);
        ps2_write_data(ms_command_queue->command);
    }
}

static int reset_mouse(unsigned char readed, unsigned char reset)
{
    static int state = 0;

    if (state == 0) {
        push_to_queue(&ms_command_queue, 0xFF, &reset_mouse);
        state = 1;
        return (1);
    }
    if (state == 1) {
        if (readed == 0xFA)
            return (0);
        if (readed == 0xAA) {
            pop_from_queue(&ms_command_queue);
            push_to_queue(&ms_command_queue, 0xF3, &reset_mouse);
            printf("Mouse self test suceed.\n\r");
            state = 2;
            return (1);
        } else {
            pop_from_queue(&ms_command_queue);
            printf("Mouse self test failed.\n\r");
            state = 0;
            return (0);
        }
    }
    if (state == 2) {
        if (readed == 0xFA) {
            pop_from_queue(&ms_command_queue);
            push_to_queue(&ms_command_queue, 80, &reset_mouse);
            state = 3;
            return (1);
        }
    }
    if (state == 3) {
        if (readed == 0xFA) {
            pop_from_queue(&ms_command_queue);
            printf("Mouse sample rate as been set to 80.\n\r");
            state = 0;
            return (0);
        }
    }
    if (reset == 1) {
        pop_from_queue(&ms_command_queue);
        state = 0;
        return (0);
    }
}

static int enable_data_reporting(unsigned char received, unsigned char reset)
{
    static int state = 0;

    if (state == 0) {
        push_to_queue(&ms_command_queue, 0xF4, &enable_data_reporting);
        state = 1;
        return (1);
    }
    if (state == 1) {
        if (received == 0xFA) {
            pop_from_queue(&ms_command_queue);
            printf("Mouse data reporting enabled.\n\r");
            state = 0;
            return (0);
        }
    }
    if (reset == 1) {
        pop_from_queue(&ms_command_queue);
        state = 0;
        return (0);
    }
    return (0);
}

mouse_status_t gs_mouse_status(mouse_move_packet_t *move_packet)
{
    static mouse_status_t mouse_status = {0, 0, 0, 0, 0, 0};

    if (move_packet == NULL) {
        return (mouse_status);
    }
    if (move_packet == 0x1) {
        mouse_status.number_of_samples = 0;
        mouse_status.delta_x = 0;
        mouse_status.delta_y = 0;
        return (mouse_status);
    }
    mouse_status.button_left_pressed = (move_packet->base_property & bit(BUTTON_LEFT)) >> BUTTON_LEFT;
    mouse_status.button_right_pressed = (move_packet->base_property & bit(BUTTON_RIGHT)) >> BUTTON_RIGHT;
    mouse_status.button_middle_pressed = (move_packet->base_property & bit(BUTTON_MIDDLE)) >> BUTTON_MIDDLE;
    mouse_status.delta_x += ((int) move_packet->x_move * ((move_packet->base_property & bit(X_AXIS_SIGN_BIT) >> X_AXIS_SIGN_BIT) ? -1 : 1)) / 2;
    mouse_status.delta_y += ((int) move_packet->y_move * ((move_packet->base_property & bit(Y_AXIS_SIGN_BIT) >> Y_AXIS_SIGN_BIT) ? -1 : 1)) / 2;
    mouse_status.number_of_samples++;
    return (mouse_status);
}

void mouse_move_handler(unsigned char readed, unsigned char reset)
{
    static int state = 0;
    static mouse_move_packet_t move_packet = {0, 0, 0};

    if (state == 0) {
        move_packet.base_property = readed;
        state = 1;
        return;
    }
    if (state == 1) {
        move_packet.x_move = readed;
        state = 2;
        return;
    }
    if (state == 2) {
        move_packet.y_move = readed;
        gs_mouse_status(&move_packet);
        state = 0;
        return;
    }
    if (reset == 1) {
        state = 0;
        return;
    }
}

void mouse_handler(void)
{
    unsigned char timeout = 0;
    unsigned char readed = ps2_read_data(&timeout);

    if (readed == 0xFE && ms_command_queue != NULL) {
        ps2_write_command(PS2_WRITE_ON_PORT_2);
        ps2_write_data(ms_command_queue->command);
        return;
    }
    if (ms_command_queue != NULL) {
        if (ms_command_queue->callback(readed, timeout) == 1)
            flush_mouse_queue();
        return;
    }
    mouse_move_handler(readed, timeout);
}

void install_mouse(void)
{
    // Port 1 and 2 have already been activated by the PS2 driver
    // Just need to install the IRQ handler, reset the keyboard
    // Set default config, and self-test it

    install_irq_handler(12, mouse_handler);
    enable_data_reporting(0, 0);
    reset_mouse(0, 0);
}