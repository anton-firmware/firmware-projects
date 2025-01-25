#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
    uint8_t id;
} event_t;

typedef struct 
{
    size_t buffer_length;
    event_t *buffer;
    uint16_t head;
    uint16_t tail;
} event_queue_t;

bool event_queue_initialise(uint8_t *buffer, size_t length);

bool event_queue_teardown(void);

bool event_queue_enqueue(event_t event);

bool event_queue_enqueue_critical(event_t event);

bool event_queue_dequeue(event_t *event);

bool event_queue_dequeue_critical(event_t *event);

#endif