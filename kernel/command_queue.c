#include "command_queue.h"

void push_to_queue(command_queue_t **queue, unsigned char command, void (*callback)(unsigned char received, int reset))
{
    command_queue_t *new_node = malloc(sizeof(command_queue_t));
    command_queue_t *act = *queue;

    new_node->callback = callback;
    new_node->command = command;
    new_node->next = *queue;
    *queue = new_node;
}

void pop_from_queue(command_queue_t **queue)
{
    command_queue_t *next = (*queue)->next;
    free(*queue);
    *queue = next;
}