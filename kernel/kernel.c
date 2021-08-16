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

//    init_acpi();
    printf("Begin malloc test.\n\r");
    char *test = malloc(sizeof(char) * 50);
    printf("%x\n\r", test);
    char *test2 = malloc(sizeof(char) * 10);
    printf("%x\n\r", test2);
    free(test2);
    test2 = malloc(sizeof(char) * 10);
    printf("%x\n\r", test2);
    free(test);
    char *test3 = malloc(sizeof(char) * 10);
    printf("%x\n\r", test3);
    printf("Malloc test end.\n\r");

    //pic_unmask_irq(0);

    __asm__ volatile("int $1");
    __asm__ volatile("int $2");
    port_byte_out(0x70, 0x00); // Tell the CMOS that we want seconds

    int time1 = port_byte_in(0x71); // Get the seconds from the RTC
    int time2 = 0;
    int frame_counter = 0;
    int start_time = time1;
    int total_frame = 0;
    int total_seconds = 0;
    unsigned char *vga_buffer = enable_graphic_256_xmode();

    int bg_color = 0x0f;
    int fg_color = 0x00;

    while (1) {
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

        vga_buffer = switch_buffers();

        frame_counter++;
        total_frame++;
        
        if ((time1 = port_byte_in(0x71)) != time2) {
            time2 = time1;
            if (frame_counter != 1) {
                total_seconds++;
                printf("%d FPS    Moy: %d\n\r", frame_counter, total_frame / total_seconds); // Will be written on serial port
            }
            frame_counter = 0;
        }
    }
}