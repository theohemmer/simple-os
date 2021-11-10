#ifndef H_KEYBOARD
#define H_KEYBOARD

void install_keyboard();
void flush_keyboard_queue(void);

typedef struct {
    int key_number;
    char name[17];
    char is_pressed;
} key_t;

/*
    Key Number:
    000   00000
    Row   Col
*/
static const key_t azerty_fr[132] = {
    {(0 << 5) | (0), "VOL_DOWN", 0},
    {(0 << 5) | (1), "VOL_UP", 0},
    {(0 << 5) | (2), "MIC_MUTE", 0},
    {(0 << 5) | (3), "SPECIAL1", 0},
    {(0 << 5) | (4), "SPECIAL2", 0},
    {(1 << 5) | (0), "ESC", 0},
    {(1 << 5) | (1), "F1", 0},
    {(1 << 5) | (2), "F2", 0},
    {(1 << 5) | (3), "F3", 0},
    {(1 << 5) | (4), "F4", 0},
    {(1 << 5) | (5), "F5", 0},
    {(1 << 5) | (6), "F6", 0},
    {(1 << 5) | (7), "F7", 0},
    {(1 << 5) | (8), "F8", 0},
    {(1 << 5) | (9), "F9", 0},
    {(1 << 5) | (10), "F10", 0},
    {(1 << 5) | (11), "F11", 0},
    {(1 << 5) | (12), "F12", 0},
    {(1 << 5) | (13), "SUPPR", 0},
    {(1 << 5) | (14), "PAUSE", 0},
    {(1 << 5) | (15), "IMPR ECR", 0},
    {(1 << 5) | (16), "END", 0},
    {(2 << 5) | (0), "SQUARE", 0},
    {(2 << 5) | (1), "1", 0},
    {(2 << 5) | (2), "2", 0},
    {(2 << 5) | (3), "3", 0},
    {(2 << 5) | (4), "4", 0},
    {(2 << 5) | (5), "5", 0},
    {(2 << 5) | (6), "6", 0},
    {(2 << 5) | (7), "7", 0},
    {(2 << 5) | (8), "8", 0},
    {(2 << 5) | (9), "9", 0},
    {(2 << 5) | (10), "0", 0},
    {(2 << 5) | (11), "°", 0},
    {(2 << 5) | (12), "+", 0},
    {(2 << 5) | (13), "BACK SPACE", 0},
    {(2 << 5) | (14), "NUM LOCK", 0},
    {(2 << 5) | (15), "NUM /", 0},
    {(2 << 5) | (16), "NUM *", 0},
    {(2 << 5) | (17), "NUM -", 0},
    {(3 << 5) | (0), "TAB", 0},
    {(3 << 5) | (1), "A", 0},
    {(3 << 5) | (2), "Z", 0},
    {(3 << 5) | (3), "E", 0},
    {(3 << 5) | (4), "R", 0},
    {(3 << 5) | (5), "T", 0},
    {(3 << 5) | (6), "Y", 0},
    {(3 << 5) | (7), "U", 0},
    {(3 << 5) | (8), "I", 0},
    {(3 << 5) | (9), "O", 0},
    {(3 << 5) | (10), "P", 0},
    {(3 << 5) | (11), "^", 0},
    {(3 << 5) | (12), "$", 0},
    {(3 << 5) | (13), "*", 0},
    {(3 << 5) | (14), "NUM 7", 0},
    {(3 << 5) | (15), "NUM 8", 0},
    {(3 << 5) | (16), "NUM 9", 0},
    {(3 << 5) | (17), "NUM +", 0},
    {(4 << 5) | (0), "CAPS LOCK", 0},
    {(4 << 5) | (1), "Q", 0},
    {(4 << 5) | (2), "S", 0},
    {(4 << 5) | (3), "D", 0},
    {(4 << 5) | (4), "F", 0},
    {(4 << 5) | (5), "G", 0},
    {(4 << 5) | (6), "H", 0},
    {(4 << 5) | (7), "J", 0},
    {(4 << 5) | (8), "K", 0},
    {(4 << 5) | (9), "L", 0},
    {(4 << 5) | (10), "M", 0},
    {(4 << 5) | (11), "%", 0},
    {(4 << 5) | (12), "ENTER", 0},
    {(4 << 5) | (13), "NUM 4", 0},
    {(4 << 5) | (14), "NUM 5", 0},
    {(4 << 5) | (15), "NUM 6", 0},
    {(5 << 5) | (0), "L SHIFT", 0},
    {(5 << 5) | (1), "<", 0},
    {(5 << 5) | (2), "W", 0},
    {(5 << 5) | (3), "X", 0},
    {(5 << 5) | (4), "C", 0},
    {(5 << 5) | (5), "V", 0},
    {(5 << 5) | (6), "B", 0},
    {(5 << 5) | (7), "N", 0},
    {(5 << 5) | (8), ",", 0},
    {(5 << 5) | (9), ";", 0},
    {(5 << 5) | (10), ":", 0},
    {(5 << 5) | (11), "!", 0},
    {(5 << 5) | (12), "R SHIFT", 0},
    {(5 << 5) | (13), "NUM 1", 0},
    {(5 << 5) | (14), "NUM 2", 0},
    {(5 << 5) | (15), "NUM 3", 0},
    {(5 << 5) | (16), "NUM ENTER", 0},
    {(6 << 5) | (0), "LEFT CTRL", 0},
    {(6 << 5) | (1), "LEFT FN", 0},
    {(6 << 5) | (2), "SUPER", 0},
    {(6 << 5) | (3), "ALT", 0},
    {(6 << 5) | (4), "SPACE", 0},
    {(6 << 5) | (5), "ALT GR", 0},
    {(6 << 5) | (6), "RIGHT FN", 0},
    {(6 << 5) | (7), "RIGHT CTRL", 0},
    {(6 << 5) | (8), "LEFT", 0},
    {(6 << 5) | (9), "UP", 0},
    {(6 << 5) | (10), "RIGHT", 0},
    {(6 << 5) | (11), "DOWN", 0},
    {(6 << 5) | (12), "NUM 0", 0},
    {(6 << 5) | (13), "NUM .", 0},
    // Special Key for PS/2 Keyboard start here
    {(7 << 5) | (0), "SCROLL LOCK", 0},
    {(7 << 5) | (1), "MULT WWW SEARCH", 0},
    {(7 << 5) | (2), "MULT PREV TRACK", 0},
    {(7 << 5) | (3), "MULT WWW FAV", 0},
    {(7 << 5) | (4), "MULT WWW REFRESH", 0},
    {(7 << 5) | (4), "MULT MUTE", 0},
    {(7 << 5) | (5), "SUPER RIGHT", 0},
    {(7 << 5) | (6), "MULT WWW STOP", 0},
    {(7 << 5) | (7), "MULT CALCULATOR", 0},
    {(7 << 5) | (8), "APP KEY", 0},
    {(7 << 5) | (9), "MULT FORWARD", 0},
    {(7 << 5) | (10), "MULT PLAY/PAUSE", 0},
    {(7 << 5) | (11), "ACPI POWER", 0},
    {(7 << 5) | (12), "MULT BACK", 0},
    {(7 << 5) | (13), "MULT WWW HOME", 0},
    {(7 << 5) | (14), "MULT STOP", 0},
    {(7 << 5) | (15), "ACPI SLEEP", 0},
    {(7 << 5) | (16), "MULT MY COMPUTER", 0},
    {(7 << 5) | (17), "MULT EMAIL", 0},
    {(7 << 5) | (18), "MULT NEXT TRACK", 0},
    {(7 << 5) | (19), "MULT SELECT", 0},
    {(7 << 5) | (20), "ACPI WAKE", 0},
    {(7 << 5) | (21), "HOME", 0},
    {(7 << 5) | (22), "INSERT", 0},
    {(7 << 5) | (23), "PAGE DOWN", 0},
    {(7 << 5) | (24), "PAGE UP", 0},
    {0b11111111, "UNKNOW", 0}
};

#define UNKNOW_KEY 151

static const unsigned char scan_code_to_key_nbr[] = {
    [0x00] = UNKNOW_KEY,
    [0x01] = 33-19,
    [0x02] = UNKNOW_KEY,
    [0x03] = 29-19,
    [0x04] = 27-19,
    [0x05] = 25-19,
    [0x06] = 26-19,
    [0x07] = 36-19,
    [0x08] = UNKNOW_KEY,
    [0x09] = 34-19,
    [0x0A] = 32-19,
    [0x0B] = 30-19,
    [0x0C] = 28-19,
    [0x0D] = 59-19,
    [0x0E] = 41-19,
    [0x0F] = UNKNOW_KEY,
    [0x10] = UNKNOW_KEY,
    [0x11] = 113-19,
    [0x12] = 93-19,
    [0x13] = UNKNOW_KEY,
    [0x14] = 110-19,
    [0x15] = 60-19,
    [0x16] = 42-19,
    [0x17] = UNKNOW_KEY,
    [0x18] = UNKNOW_KEY,
    [0x19] = UNKNOW_KEY,
    [0x1A] = 95-19,
    [0x1B] = 79-19,
    [0x1C] = 78-19,
    [0x1D] = 61-19,
    [0x1E] = 43-19,
    [0x1F] = UNKNOW_KEY,
    [0x20] = UNKNOW_KEY,
    [0x21] = 97-19,
    [0x22] = 96-19,
    [0x23] = 80-19,
    [0x24] = 62-19,
    [0x25] = 45-19,
    [0x26] = 44-19,
    [0x27] = UNKNOW_KEY,
    [0x28] = UNKNOW_KEY,
    [0x29] = 114-19,
    [0x2A] = 98-19,
    [0x2B] = 81-19,
    [0x2C] = 64-19,
    [0x2D] = 63-19,
    [0x2E] = 46-19,
    [0x2F] = UNKNOW_KEY,
    [0x30] = UNKNOW_KEY,
    [0x31] = 100-19,
    [0x32] = 99-19,
    [0x33] = 83-19,
    [0x34] = 82-19,
    [0x35] = 65-19,
    [0x36] = 47-19,
    [0x37] = UNKNOW_KEY,
    [0x38] = UNKNOW_KEY,
    [0x39] = UNKNOW_KEY,
    [0x3A] = 101-19,
    [0x3B] = 84-19,
    [0x3C] = 66-19,
    [0x3D] = 48-19,
    [0x3E] = 49-19,
    [0x3F] = UNKNOW_KEY,
    [0x40] = UNKNOW_KEY,
    [0x41] = 102-19,
    [0x42] = 85-19,
    [0x43] = 67-19,
    [0x44] = 68-19,
    [0x45] = 51-19,
    [0x46] = 50-19,
    [0x47] = UNKNOW_KEY,
    [0x48] = UNKNOW_KEY,
    [0x49] = 103-19,
    [0x4A] = 104-19,
    [0x4B] = 86-19,
    [0x4C] = 87-19,
    [0x4D] = 69-19,
    [0x4E] = 52-19,
    [0x4F] = UNKNOW_KEY,
    [0x50] = UNKNOW_KEY,
    [0x51] = UNKNOW_KEY,
    [0x52] = 88-19,
    [0x53] = UNKNOW_KEY,
    [0x54] = 70-19,
    [0x55] = 53-19,
    [0x56] = UNKNOW_KEY,
    [0x57] = UNKNOW_KEY,
    [0x58] = 77-19,
    [0x59] = 105-19,
    [0x5A] = 89-19,
    [0x5B] = 71-19,
    [0x5C] = UNKNOW_KEY,
    [0x5D] = 72-19,
    [0x5E] = UNKNOW_KEY,
    [0x5F] = UNKNOW_KEY,
    [0x60] = UNKNOW_KEY,
    [0x61] = UNKNOW_KEY,
    [0x62] = UNKNOW_KEY,
    [0x63] = UNKNOW_KEY,
    [0x64] = UNKNOW_KEY,
    [0x65] = UNKNOW_KEY,
    [0x66] = 54-19,
    [0x67] = UNKNOW_KEY,
    [0x68] = UNKNOW_KEY,
    [0x69] = 106-19,
    [0x6A] = UNKNOW_KEY,
    [0x6B] = 90-19,
    [0x6C] = 73-19,
    [0x6D] = UNKNOW_KEY,
    [0x6E] = UNKNOW_KEY,
    [0x6F] = UNKNOW_KEY,
    [0x70] = 122-19,
    [0x71] = 123-19,
    [0x72] = 107-19,
    [0x73] = 91-19,
    [0x74] = 92-19,
    [0x75] = 74-19,
    [0x76] = 24-19,
    [0x77] = 55-19,
    [0x78] = 35-19,
    [0x79] = 76-19,
    [0x7A] = 108-19,
    [0x7B] = 58-19,
    [0x7C] = 57-19,
    [0x7D] = 75-19,
    [0x7E] = 125-19, // SCROLL LOCK?
    [0x7F] = UNKNOW_KEY,
    [0x80] = UNKNOW_KEY,
    [0x81] = UNKNOW_KEY,
    [0x82] = UNKNOW_KEY,
    [0x83] = 31-19
};

static const unsigned char scan_code_e0_to_key_nbr[] = {
    [0x00] = UNKNOW_KEY,
    [0x01] = UNKNOW_KEY,
    [0x02] = UNKNOW_KEY,
    [0x03] = UNKNOW_KEY,
    [0x04] = UNKNOW_KEY,
    [0x05] = UNKNOW_KEY,
    [0x06] = UNKNOW_KEY,
    [0x07] = UNKNOW_KEY,
    [0x08] = UNKNOW_KEY,
    [0x09] = UNKNOW_KEY,
    [0x0A] = UNKNOW_KEY,
    [0x0B] = UNKNOW_KEY,
    [0x0C] = UNKNOW_KEY,
    [0x0D] = UNKNOW_KEY,
    [0x0E] = UNKNOW_KEY,
    [0x0F] = UNKNOW_KEY,
    [0x10] = 126-19, // Multimedia, WWW search
    [0x11] = 115-19,
    [0x12] = UNKNOW_KEY,
    [0x13] = UNKNOW_KEY,
    [0x14] = 117-19,
    [0x15] = 127-18, // Multimedia, Previous track
    [0x16] = UNKNOW_KEY,
    [0x17] = UNKNOW_KEY,
    [0x18] = 128-19, // Multimedia, WWW favourites
    [0x19] = UNKNOW_KEY,
    [0x1A] = UNKNOW_KEY,
    [0x1B] = UNKNOW_KEY,
    [0x1C] = UNKNOW_KEY,
    [0x1D] = UNKNOW_KEY,
    [0x1E] = UNKNOW_KEY,
    [0x1F] = 112-19, // Left GUI Key (super key)
    [0x20] = 129-19, // Multimedia, WWW refresh
    [0x21] = 19-19, // Multimedia, Volume down
    [0x22] = UNKNOW_KEY,
    [0x23] = 130-19, // Multimedia, Mute
    [0x24] = UNKNOW_KEY,
    [0x25] = UNKNOW_KEY,
    [0x26] = UNKNOW_KEY,
    [0x27] = 131-19, // Right GUI Key (super key)
    [0x28] = 132-19, // Multimedia, WWW stop
    [0x29] = UNKNOW_KEY,
    [0x2A] = UNKNOW_KEY,
    [0x2B] = 133-19, // Multimedia, Calculator
    [0x2C] = UNKNOW_KEY,
    [0x2D] = UNKNOW_KEY,
    [0x2F] = 134-19, // Apps key
    [0x30] = 135-19, // Multimedia, forward
    [0x31] = UNKNOW_KEY,
    [0x32] = 20-19, // Multimedia, Volume up
    [0x33] = UNKNOW_KEY,
    [0x34] = 136-19, // Multimedia, Play / Pause
    [0x35] = UNKNOW_KEY,
    [0x36] = UNKNOW_KEY,
    [0x37] = 137-19, // ACPI, power
    [0x38] = 138-19, // Multimedia, Back pressed
    [0x39] = UNKNOW_KEY,
    [0x3A] = 139-19, // Multimedia, WWW home
    [0x3B] = 140-19, // Multimedia, stop
    [0x3C] = UNKNOW_KEY,
    [0x3D] = UNKNOW_KEY,
    [0x3F] = 141-19, // ACPI, sleep
    [0x40] = 142-19, // Multimedia, my computer
    [0x41] = UNKNOW_KEY,
    [0x42] = UNKNOW_KEY,
    [0x43] = UNKNOW_KEY,
    [0x44] = UNKNOW_KEY,
    [0x45] = UNKNOW_KEY,
    [0x46] = UNKNOW_KEY,
    [0x47] = UNKNOW_KEY,
    [0x48] = 143-19, // Multimedia, email
    [0x49] = UNKNOW_KEY,
    [0x4A] = 46-19,
    [0x4B] = UNKNOW_KEY,
    [0x4C] = UNKNOW_KEY,
    [0x4D] = 144-19, // Multimedia, Next track
    [0x4E] = UNKNOW_KEY,
    [0x4F] = UNKNOW_KEY,
    [0x50] = 145-19, // Multimedia, Select
    [0x51] = UNKNOW_KEY,
    [0x52] = UNKNOW_KEY,
    [0x53] = UNKNOW_KEY,
    [0x54] = UNKNOW_KEY,
    [0x55] = UNKNOW_KEY,
    [0x56] = UNKNOW_KEY,
    [0x57] = UNKNOW_KEY,
    [0x58] = UNKNOW_KEY,
    [0x59] = UNKNOW_KEY,
    [0x5A] = 109-19,
    [0x5B] = UNKNOW_KEY,
    [0x5C] = UNKNOW_KEY,
    [0x5D] = UNKNOW_KEY,
    [0x5E] = 146-19, // ACPI, wake
    [0x5F] = UNKNOW_KEY,
    [0x60] = UNKNOW_KEY,
    [0x61] = UNKNOW_KEY,
    [0x62] = UNKNOW_KEY,
    [0x63] = UNKNOW_KEY,
    [0x64] = UNKNOW_KEY,
    [0x65] = UNKNOW_KEY,
    [0x66] = UNKNOW_KEY,
    [0x67] = UNKNOW_KEY,
    [0x68] = UNKNOW_KEY,
    [0x69] = 40-19,
    [0x6A] = UNKNOW_KEY,
    [0x6B] = 118-19,
    [0x6C] = 147-19, // Home
    [0x6D] = UNKNOW_KEY,
    [0x6E] = UNKNOW_KEY,
    [0x6F] = UNKNOW_KEY,
    [0x70] = 148-19, // Insert
    [0x71] = 37-19,
    [0x72] = 121-19,
    [0x73] = UNKNOW_KEY,
    [0x74] = 120-19,
    [0x75] = 119-19,
    [0x76] = UNKNOW_KEY,
    [0x77] = UNKNOW_KEY,
    [0x78] = UNKNOW_KEY,
    [0x79] = UNKNOW_KEY,
    [0x7A] = 149-19, // Page Down
    [0x7B] = UNKNOW_KEY,
    [0x7C] = UNKNOW_KEY,
    [0x7D] = 150-19, // Page Up
};

#endif