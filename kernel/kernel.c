#include "driver/vga_graphic_mode.h"
#include "interrupts/isr.h"
#include "interrupts/irq.h"
#include "interrupts/idt.h"
#include "kernel/lib/include/stdio.h"
#include "kernel/lib/include/string.h"
#include <stddef.h>
#include <stdint.h>
#include "driver/port.h"
#include "driver/pic.h"
#include "driver/acpi.h"
#include "driver/ps2.h"
#include "driver/keyboard.h"
#include "driver/mouse.h"
#include "kernel/lib/include/stdlib.h"

void main() {
    pic_first_init();
    registers_isr();
    registers_irq();
    register_the_idt();

    pic_unmask_irq(1);
    pic_unmask_irq(2);
    pic_unmask_irq(12);

    ps2_enable();
    install_keyboard();
    install_mouse();

    int mouse_x = 320/2;
    int mouse_y = 200/2;
    int mouse_left_pressed = 0;
    int mouse_right_pressed = 0;
    int mouse_middle_pressed = 0;
    mouse_status_t mouse_status;

//    init_acpi();
    printf(" /-> Begin malloc/free test.\n\r");
    char *test = malloc(sizeof(char) * 50);
    printf(" | 1: 0x%x MALLOC 50 (should not be to far form 0x100000)\n\r", test);
    char *test2 = malloc(sizeof(char) * 10);
    printf(" | 2: 0x%x MALLOC 10 (should be more than 1)\n\r", test2);
    free(test2);
    test2 = malloc(sizeof(char) * 10);
    printf(" | 3: 0x%x FREE(2) MALLOC 10 (should be the same as 2)\n\r", test2);
    free(test);
    char *test3 = malloc(sizeof(char) * 10);
    printf(" | 4: 0x%x FREE(1) MALLOC 10 (should be the same as 1)\n\r", test3);
    free(test3);
    test3 = malloc(sizeof(char) * 50);
    printf(" | 5: 0x%x FREE(4) MALLOC 50 (should be the same as 1&4)\n\r", test3);
    printf(" \\-> Malloc/free test end.\n\r");

    //pic_unmask_irq(0);

    __asm__ volatile("cli");
    port_byte_out(0x70, 0x00); // Tell the CMOS that we want seconds
    __asm__ volatile("sti");

    int time1 = port_byte_in(0x71); // Get the seconds from the RTC
    int time2 = 0;
    int frame_counter = 0;
    int start_time = time1;
    int total_frame = 0;
    int total_seconds = 0;
    int moy_fps = 0;
    unsigned char *vga_buffer = enable_graphic_256_xmode();

    int bg_color = 0x0f;
    int fg_color = 0x00;

    key_t coucou;
    for (int i = 0; i < 105; i++) {
        coucou = azerty_fr[i];
        printf("%b %s\n", coucou.key_number, coucou.name);
    }

    while (1) {
        mouse_status = gs_mouse_status(NULL);
        if (mouse_status.button_right_pressed != mouse_right_pressed) {
            if (mouse_status.button_right_pressed)
                printf("Mouse right click pressed.\n\r");
            else
                printf("Mouse right click rellased.\n\r");
            mouse_right_pressed = mouse_status.button_right_pressed;
        }
        if (mouse_status.button_left_pressed != mouse_left_pressed) {
            if (mouse_status.button_left_pressed)
                printf("Mouse left click pressed.\n\r");
            else
                printf("Mouse left click rellased.\n\r");
            mouse_left_pressed = mouse_status.button_left_pressed;
        }
        if (mouse_status.button_middle_pressed != mouse_middle_pressed) {
            if (mouse_status.button_middle_pressed)
                printf("Mouse middle click pressed.\n\r");
            else
                printf("Mouse middle click rellased.\n\r");
            mouse_middle_pressed = mouse_status.button_middle_pressed;
        }
        if (mouse_status.number_of_samples > 0 && moy_fps != 0) {
            printf("Number of samples: %d\n\r Delta X: %d\n\r Delta Y: %d\n\r", mouse_status.number_of_samples, mouse_status.delta_x, mouse_status.delta_y);
            mouse_x += (mouse_status.delta_x / mouse_status.number_of_samples);
            mouse_y += -(mouse_status.delta_y / mouse_status.number_of_samples);
        } else {
            mouse_x += mouse_status.delta_x;
            mouse_y += -mouse_status.delta_y;
        }
        gs_mouse_status(0x1);
        mouse_x = (mouse_x > 319) ? 319 : mouse_x;
        mouse_x = (mouse_x < 0) ? 0 : mouse_x;
        mouse_y = (mouse_y > 199) ? 199 : mouse_y;
        mouse_y = (mouse_y < 0) ? 0 : mouse_y;
        for (int y = 0; y < 200; y++) {
            for (int x = 0; x < 320; x++) {
                fg_color = 0x00;
                bg_color = 0x0f;
                if (vga_buffer == (unsigned char *) VGA_FRONT_BUFFER) {
                    bg_color = 0x00;
                    fg_color = 0x0f;
                }
                if (y == 0)
                    put_a_pixel(x, y, bg_color, vga_buffer);
                else if (x == 0)
                    put_a_pixel(x, y, bg_color, vga_buffer);
                else if (x == 319)
                    put_a_pixel(x, y, bg_color, vga_buffer);
                else if (y == 199)
                    put_a_pixel(x, y, bg_color, vga_buffer);
                else
                    put_a_pixel(x, y, 0x00, vga_buffer);
            }
        }

        for (int y = -2; y < 2; y++) {
            for (int x = -2; x < 2; x++) {
                int pos_x = mouse_x + x;
                int pos_y = mouse_y + y;
                pos_x = (pos_x > 319) ? 319 : pos_x;
                pos_x = (pos_x < 0) ? 0 : pos_x;
                pos_y = (pos_y > 199) ? 199 : pos_y;
                pos_y = (pos_y < 0) ? 0 : pos_y;
                put_a_pixel(pos_x, pos_y, 0x10, vga_buffer);
            }
        }

        vga_buffer = switch_buffers();

        frame_counter++;
        total_frame++;
        
        if ((time1 = port_byte_in(0x71)) != time2) {
            //printf("Time S: %d\n", time1);
            time2 = time1;
            if (frame_counter != 1) {
                total_seconds++;
                moy_fps = total_frame / total_seconds;
                //printf("%d FPS    Moy: %d\n\r", frame_counter, total_frame / total_seconds); // Will be written on serial port
            }
            frame_counter = 0;
        }
        flush_keyboard_queue();
        flush_mouse_queue();
    }
}