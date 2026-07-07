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
    uint32_t start_time;
    timer_srv_t* next;
} timer_srv_t;

static timer_srv_t timers_pool[MAX_TIMERS];

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

    return true;
}

bool init_timer( timer_srv_t* timer_ptr )
{
    if (timer_ptr == NULL)
    {
        return false;
    }
    timer_ptr->period_ms = 0;
    timer_ptr->call_back = NULL;
    timer_ptr->periodic = false;
    timer_ptr->start_time = 0;
    return true;
}

bool init_timers( timer_srv_t* pool_addr, uint32_t max_timers )
{
    if (pool_addr == NULL)
    {
        return false;
    }

    for ( uint32_t i=0; i<max_timers; i++)
    {
        if ( init_timer(&pool_addr[i]) == false )
        {
            return false;
        }
    }
    return true;
}

timer_srv_t* allocate_timer( timer_srv_t** free_list )
{
    if ( free_list == NULL )
    {
        return NULL;
    }

    timer_srv_t* allocated_timer = *free_list;
    *free_list = allocated_timer->next;
    allocated_timer->next = NULL;

    return allocated_timer;
}

bool activate_timer( timer_srv_t* allocated_node, timer_srv_t** active_list )
{
    if ( allocated_node == NULL || active_list == NULL)
    {
        return false;
    }

    allocated_node->next = *active_list;
    *active_list = allocated_node;
    allocated_node->start_time = get_time_now();  // take current timestamp - as timer is activated
    
    return true;
}

// move timer node from active list to free list
bool release_timer( timer_srv_t* timer_node, timer_srv_t** active_list, timer_srv_t** free_list )
{
    if ( timer_node == NULL || active_list == NULL || free_list == NULL )
    {
        return false;
    }

    timer_srv_t* active_list_ptr = *active_list;
    timer_srv_t* prev_node = *active_list;
    bool timer_is_found = false;

    // if the first node of active list is the one we should release - remove it from active list
    if ( active_list_ptr == timer_node )
    {
        *active_list = (*active_list)->next;  // override head with new head (next node)
        //timer_node->next = NULL;

        // push the node which released to the head of free list
        timer_node->next = *free_list;
        *free_list = timer_node;        // override the new head as the node we released
        return true;
    }

    // find the timer address we should release and release it - remove it from active list
    while ( active_list_ptr != NULL)
    {
        if ( active_list_ptr == timer_node )
        {
            timer_is_found = true;
            prev_node->next = active_list_ptr->next;
            active_list_ptr->next = NULL;
            break;
        }
        prev_node = active_list_ptr;
        active_list_ptr = active_list_ptr->next;
    }

    if ( timer_is_found )
    {
        // push the node which released to the head of free list
        timer_node->next = *free_list;
        *free_list = timer_node;        // override the new head as the node we released
        return true;
    }
    return false;
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

// to do: update active and free list
// after releasing the timer - should be checked
void monitor_timers( timer_srv_t* active_list, timer_srv_t* free_list )
{
    if ( active_list == NULL )
    {
        return;
    }

    timer_srv_t* current_node = active_list;

    uint32_t time_now = get_time_now();

    while (current_node != NULL )
    {
        if ( (time_now - current_node->start_time) >= current_node->period_ms )
        {
            current_node->call_back();
            
            if ( current_node->periodic )
            {
                current_node->start_time += current_node->period_ms;
            }
            else
            {
                release_timer( current_node, &active_list, &free_list );
            }
        }
        current_node = current_node->next;
    }
}

bool connect_timer_nodes( timer_srv_t* timers_ptr, uint32_t max_timers )
{
    if ( timers_ptr == NULL || max_timers == 0 )
    {
        return false;
    }

    if ( max_timers == 1 )
    {
        timers_ptr[0].next = NULL;
        return true;
    }

    uint32_t i = 0;

    while (i<(max_timers-1))
    {
        timers_ptr[i].next = &timers_ptr[i+1];
        i++;
    }
    timers_ptr[i].next = NULL;
    return true;
}

int main( void )
{

    timer_srv_t* free_list = timers_pool;
    timer_srv_t* active_list = NULL;

    // init all timers
    init_timers( timers_pool, MAX_TIMERS );

    // connect timers nodes
    connect_timer_nodes( timers_pool, MAX_TIMERS );

    timer_srv_t* timer1 = allocate_timer( &free_list );
    timer_srv_t* timer2 = allocate_timer( &free_list );

    config_timer( timer1, task1, 500, true, 1);   // periodic timer - every 500ms
    config_timer( timer2, task1, 120, false, 1);  // oneshot timer - trigger once after 120ms

    activate_timer( timer1, &active_list);
    activate_timer( timer2, &active_list);

    // super loop
    while(1)
    {
        monitor_timers(active_list);
    }
}