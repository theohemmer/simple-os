#ifndef H_MOUSE
#define H_MOUSE

#define Y_AXIS_OVERFLOW 7
#define X_AXIS_OVERFLOW 6
#define Y_AXIS_SIGN_BIT 5
#define X_AXIS_SIGN_BIT 4
#define BUTTON_MIDDLE   2
#define BUTTON_RIGHT    1
#define BUTTON_LEFT     0

typedef struct {
    unsigned char base_property;
    char x_move;
    char y_move;
} mouse_move_packet_t;

typedef struct {
    unsigned char button_middle_pressed;
    unsigned char button_right_pressed;
    unsigned char button_left_pressed;
    int delta_x;
    int delta_y;
    int number_of_samples;
} mouse_status_t;

void flush_mouse_queue(void);
void install_mouse(void);
mouse_status_t gs_mouse_status(mouse_move_packet_t *move_packet);

#endif