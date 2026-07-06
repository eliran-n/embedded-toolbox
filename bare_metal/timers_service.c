#include <stdint.h>
#include <stdbool.h>

/* Task: Software Timer Implementation in C 

Context: 
- System Type: Bare Metal (No Operating System). 
- Hardware Support: There is a single hardware timer that triggers an interrupt once every 1 millisecond (1ms). 
- Target Capability: Implement a software timer mechanism that can handle up to 20 concurrent software timers. 

Requirements & Specifications: 
- Support up to 20 software timers. 
- Timer types must support both 'Repeating' (periodic) and 'One-Shot' modes. 
- Each timer must trigger a custom callback function when it expires. 
- Constraints: No Operating System, no preemption, and no priorities. 

Tasks to Implement: 
1. Define the timer structure ('struct timer'). 
2. Implement the Hardware Timer Interrupt Service Routine (ISR) logic. 
3. Implement the background processing logic inside the 'super_loop'. 
4. Write the system's external API functions (e.g., start, stop, create). 

*/

#define MAX_TIMERS 20

typedef void (*timer_cb)(void);

typedef struct timer_srv_t
{
    uint32_t period_ms;
    timer_cb call_back;
    bool periodic;
    bool in_use;
    bool active;
    uint32_t start_time;
} timer_srv_t;

static timer_srv_t timers_srv[MAX_TIMERS];
static volatile uint32_t time_counter = 0;

bool config_timer( timer_srv_t* srv_ptr, timer_cb func_ptr, uint32_t period, bool periodic, bool active_flag )
{
    if (srv_ptr == NULL)
    {
        return false;
    }
    srv_ptr->period_ms = period;
    srv_ptr->call_back = func_ptr;
    srv_ptr->periodic = periodic;
    srv_ptr->active = active_flag;

    if ( active_flag )
    {
        srv_ptr->start_time = get_time_now(); // take current timestamp
    }
    else
    {
        srv_ptr->start_time = 0;
    }
    
    return true;
}

bool init_timer( timer_srv_t* srv_ptr )
{
    if (srv_ptr == NULL)
    {
        return false;
    }
    srv_ptr->period_ms = 0;
    srv_ptr->call_back = NULL;
    srv_ptr->periodic = false;
    srv_ptr->active = false;
    srv_ptr->in_use = false;
    srv_ptr->start_time = 0;
    return true;
}

bool init_timers( timer_srv_t* timers_struct_addr )
{
    if (timers_struct_addr == NULL)
    {
        return false;
    }

    for ( uint32_t i=0; i<MAX_TIMERS; i++)
    {
        if ( (init_timer(&timers_struct_addr[i])) == false )
        {
            return false;
        }
    }

    return true;
}

timer_srv_t* allocate_timer( timer_srv_t* timers_struct_addr )
{
    if ( timers_struct_addr == NULL )
    {
        return NULL;
    }

    for (uint32_t i=0; i<MAX_TIMERS; i++)
    {
        if ( timers_struct_addr[i].in_use == false )
        {
            // set timer as in use
            timers_struct_addr[i].in_use = true;
            // return the timer address
            return &timers_struct_addr[i];
        }
    }
    return NULL;
}

bool free_timer(timer_srv_t* timer)
{
    if ( timer == NULL )
    {
        return false;
    }

    timer->active = false;
    timer->in_use = false;
    timer->call_back = NULL;
    timer->period_ms = 0;
    timer->periodic = false;
    timer->start_time = 0;
    
    return true;
}

void task1( void )
{
    //....
}

void task2( void )
{
    //....
}

void systick_interrupt_handler( void )
{
    time_counter++;
}

uint32_t get_time_now( void )
{  
    uint32_t current_time;

    disable_irq();
    current_time = time_counter;
    enable_irq();

    return current_time;
}

void monitor_timers( timer_srv_t* timers )
{
    uint32_t time_now = get_time_now();

    for (uint32_t i=0; i<MAX_TIMERS; i++)
    {
        if ( timers[i].active )
        {
            if ( ( time_now - timers[i].start_time ) >= timers[i].period_ms )
            {
                if ( timers[i].call_back != NULL )
                {   
                    // trigger function
                    timers[i].call_back();
                }
                
                if ( timers[i].periodic )
                {
                    timers[i].start_time += timers[i].period_ms;
                }
                // in case it's oneshot
                else
                {
                    // free and deactivate the timer
                    free_timer(&timers[i]);
                }
            }
        }
    }
}

int main( void )
{
    // init all timers
    init_timers( timers_srv );

    timer_srv_t* timer1 = allocate_timer( timers_srv );
    timer_srv_t* timer2 = allocate_timer( timers_srv );

    config_timer( timer1, task1, 500, true, 1);   // periodic timer - every 500ms
    config_timer( timer2, task1, 120, false, 1);  // oneshot timer - trigger once after 120ms

    // super loop
    while(1)
    {
        monitor_timers(timers_srv);
    }
}