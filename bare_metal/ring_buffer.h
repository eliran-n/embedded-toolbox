#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define QUEUE_SIZE 100

typedef struct queue
{
    int32_t data[QUEUE_SIZE];
    uint32_t rear;  // point to the next availabe cell
    uint32_t front; // point to the current element waiting in queue
    uint32_t count; // count the num of elements currently in the queue
} queue_t;

bool enqueue( queue_t* queue_ptr, int32_t value );
bool dequeue( queue_t* queue_ptr, int32_t* value );
bool queue_is_empty( queue_t* queue_ptr );
bool queue_is_full( queue_t* queue_ptr );
bool queue_init( queue_t* queue_ptr );

#endif