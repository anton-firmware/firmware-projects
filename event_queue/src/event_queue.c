#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "event_queue.h"
#include "hal_core_interrupts.h"

static volatile event_queue_t queue;

static inline bool is_queue_full(void)
{
    return ((queue.tail + 1u) % queue.buffer_length) == queue.head;
}

static inline bool is_queue_empty(void)
{
    return queue.tail == queue.head;
}

bool event_queue_initialise(event_t *buffer, size_t length)
{
    bool result = false;

    if (buffer != NULL && length != 0)
    {
        queue.buffer = buffer;
        queue.buffer_length = length;
        queue.head = 0u;
        queue.tail = 0u;
		result = true;
    }
    
    return result;
}

void event_queue_teardown(void)
{
    queue.buffer = NULL;
    queue.buffer_length = 0;
    queue.head = 0u;
    queue.tail = 0u;
}

bool event_queue_enqueue(event_t event)
{
    bool result = false;

    if (queue.buffer != NULL && !is_queue_full())
    {
        queue.buffer[queue.head] = event;
        queue.head = (queue.head + 1u) % queue.buffer_length;
        result = true;
    }
    
    return result;
}

bool event_queue_enqueue_critical(event_t event)
{
    bool result = false;

    hal_interrupts_disable();
    result = event_queue_enqueue(event);
    hal_interrupts_enable();
    
    return result;
}

bool event_queue_dequeue(event_t *event)
{
    bool result = false;

    if (event != NULL && queue.buffer != NULL && !is_queue_empty())
    {
        *event = queue.buffer[queue.tail];
        queue.tail = (queue.tail + 1u) % queue.buffer_length;
		result = true;
    }

    return result;
}

bool event_queue_dequeue_critical(event_t *event)
{
    bool result = false;

    hal_interrupts_disable();
    result = event_queue_dequeue(event);
    hal_interrupts_enable();
    
    return result;
}
