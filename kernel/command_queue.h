#ifndef H_COMMAND_QUEUE
#define H_COMMAND_QUEUE

typedef struct command_queue_s {
    unsigned char command;
    void (*callback)(unsigned char received, int reset);
    struct command_queue_s *next;
} command_queue_t;

void push_to_queue(command_queue_t **queue, unsigned char command, void (*callback)(unsigned char received, int reset));
void pop_from_queue(command_queue_t **queue);

#endif