#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stddef.h>
#include <stdint.h>

typedef struct 
{
    uint8_t id;
} event_t;

typedef struct 
{
    size_t buffer_length;
    uint8_t *buffer;
    uint16_t head;
    uint16_t tail;
} event_queue_t;

bool event_queue_initialise(uint8_t *buffer)

#endif