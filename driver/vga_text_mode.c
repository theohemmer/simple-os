#include "vga_text_mode.h"
#include <stdint.h>
#include <stddef.h>

static inline uint8_t make_color(int blink, int fg, int bg)
{
    if (blink)
        return BLINK | fg | (bg << 4);
    return STATIC | fg | (bg << 4);
}

static inline uint16_t make_char(char c, uint8_t color)
{
    return (uint16_t) c | ((uint16_t) color << 8);
}

void put_char_on_screen(char c, int x, int y)
{
    uint16_t *vga_buffer = (uint16_t *) 0xb8000;
    uint8_t color = make_color(0, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    uint16_t to_put = make_char(c, color);
    size_t idx = y * VGA_WIDTH + x;
    vga_buffer[idx] = to_put;
}

void scroll_up()
{
    uint16_t *vga_buffer = (uint16_t *) 0xb8000;

    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            size_t idx = y * VGA_WIDTH + x;
            size_t to_idx = (y - 1) * VGA_WIDTH + x;
            vga_buffer[to_idx] = vga_buffer[idx];
            vga_buffer[idx] = (uint16_t) ' ' | ((uint16_t) (0 | VGA_COLOR_WHITE | (VGA_COLOR_BLACK << 4)) << 8);
        }
    }
}

void write_string(const char *string)
{
    static size_t line = 0;
    static size_t x = 0;

    for (int i = 0; string[i]; i++) {
        if (string[i] == '\n') {
            x = 0;
            line++;
        } else if (string[i] == '\r') {
            x = 0;
        } else {
            put_char_on_screen(string[i], x, line);
            x++;
            if (x > VGA_WIDTH) {
                x = 0;
                line++;
            }
        }
        if (line >= VGA_HEIGHT) {
            scroll_up();
            line--;
        }
    }
}