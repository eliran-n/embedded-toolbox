#include <stdint.h>
#include <stdbool.h>
#include "ring_buffer.h"

typedef struct Semaphore
{
    uint32_t count;
    uint32_t max_count;
} semaphore_t;

bool semaphore_give( semaphore_t* sem );
bool semaphore_take( semaphore_t* sem );
bool semaphore_init( semaphore_t* sem, uint32_t max_count );

static semaphore_t semaphore;
static queue_t queue;

bool semaphore_give( semaphore_t* sem )
{
    if ( sem == NULL )
    {
        return false;
    }

    __disable_irq();
    
    if ( sem->count < sem->max_count )
    {
        sem->count++;
        __enable_irq();
        return true;
    }
    __enable_irq();
    return false;
}

bool semaphore_take( semaphore_t* sem )
{
    if ( sem == NULL )
    {
        return false;
    }

    __disable_irq();

    if ( (sem->count) > 0 )
    {
        sem->count--;
        __enable_irq();
        return true;
    }
    __enable_irq();
    return false;
}

bool semaphore_init( semaphore_t* sem, uint32_t max_count )
{
    if ( sem == NULL )
    {
        return false;
    }
    sem->count = 0;
    sem->max_count = max_count;
    return true;
}

void adc_irq_handler( void )
{
    uint32_t adc_val = read_adc_from_register();
    enqueue(&queue, adc_val);
    semaphore_give(&semaphore);
}

void process_adc_sample( void )
{
    uint32_t adc_val;

    if ( semaphore_take(&semaphore) )
    {
        if ( dequeue(&queue, &adc_val) )
        {
            procces_adc(adc_val);
        }
    }
}

int main ( void )
{
    queue_init(&queue);
    semaphore_init(&semaphore, 1);

    while(1)
    {
        process_adc_sample();
    }
    return 0;
}