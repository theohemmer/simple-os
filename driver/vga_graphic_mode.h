#ifndef H_VGA_GRAPHIC_MODE
#define H_VGA_GRAPHIC_MODE

#define VGA_FRONT_BUFFER 0xA0000
#define VGA_BACK_BUFFER  0xAFFFF

/*!
    Enable the 256 mode x
    \return The address of the actual front buffer
*/
unsigned char *enable_graphic_256_xmode();

/*!
    Switch back buffer and front buffer
    When called, This functions wait for VGA Vertical Retrace before returning
    It helps to eliminate screen flickering
    \return The address of the back buffer
*/
unsigned char *switch_buffers();

/*!
    Draw a pixel on the screen
    \param x X position on screen
    \param y Y position on screen
    \param color index of the color in the VGA DAC
    \param buffer the buffer to write (usually the back buffer)
*/
void put_a_pixel(int x, int y, int color, unsigned char *buffer);

/*!
    Change a color in the VGA DAC
    \param r red value
    \param g grenn value
    \param b blue value
    \param index the index where the color will be written on the DAC
*/
void change_color_in_dac(unsigned char r, unsigned char g, unsigned char b, unsigned char index);

void display_letter(unsigned char letter, int bg_color, int fg_color, unsigned char *buffer, int x, int y);

#endif