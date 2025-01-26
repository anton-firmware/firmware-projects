#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/** Structure representing an event. */
typedef struct 
{
    uint8_t id; /*!< ID of the event. */
	uint8_t byte; /*!< Optional byte of data. */
} event_t;

/** Structure representing the event queue. */
typedef struct 
{
    size_t buffer_length; /*!< Size of the buffer in bytes. */
    event_t *buffer; /*!< Pointer to an array of events. */
    uint16_t head; /*!< Index of the front of the queue. */
    uint16_t tail; /*!< Index of the back of the queue. */
} event_queue_t;

/** Initialise the event queue.
 * 
 * \param[in] buffer Pointer to buffer of events for the queue to use.
 * \param[in] length Size of the queue in bytes.
 * 
 * \returns \c true if successful, \c false otherwise.
 */
bool event_queue_initialise(event_t *buffer, size_t length);

/** Teardown the event queue. */
void event_queue_teardown(void);

/** Enqueue an event.
 * 
 * \param[in] event The event to enqueue.
 * 
 * \returns \c true if successful, \c false if the event queue was full or uninitialised.
 */
bool event_queue_enqueue(event_t event);

/** Enqueue an event with a critical section.
 * 
 * \param[in] event The event to enqueue.
 * 
 * \returns \c true if successful, \c false if the event queue was full or uninitialised.
 */
bool event_queue_enqueue_critical(event_t event);

/** Dequeue an event.
 * 
 * \param[out] event The dequeued event.
 * 
 * \returns \c true if successful, \c false if the event queue was empty, unitialised, or 
 *          the event pointer was \c NULL.
 */
bool event_queue_dequeue(event_t *event);

/** Dequeue an event with a critical section.
 * 
 * \param[out] event The dequeued event.
 * 
 * \returns \c true if successful, \c false if the event queue was empty, unitialised, or 
 *          the event pointer was \c NULL.
 */
bool event_queue_dequeue_critical(event_t *event);

#endif
