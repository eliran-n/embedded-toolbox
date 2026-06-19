#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 10

typedef struct stack
{
    int32_t data[STACK_SIZE];
    int32_t top;
} stack_t;

bool stack_init( stack_t* stack_ptr );
bool stack_push(stack_t* stack_ptr, int32_t value);
bool stack_pop(stack_t* stack_ptr, int32_t* value);
bool stack_peek(stack_t* stack_ptr, int32_t* value);
bool stack_is_empty(stack_t* stack_ptr);
bool stack_is_full(stack_t* stack_ptr);


bool stack_push( stack_t* stack_ptr, int32_t value )
{
    if ( stack_ptr == NULL )
    {
        return false;
    }

    if ( stack_is_full(stack_ptr) )
    {
        return false;
    }

    stack_ptr->top++;
    stack_ptr->data[stack_ptr->top] = value;
    return true;
}

bool stack_pop( stack_t* stack_ptr, int32_t* value )
{
    if ( stack_ptr == NULL || value == NULL )
    {
        return false;
    }

    if ( stack_is_empty(stack_ptr) )
    {
        return false;
    }

    *value = stack_ptr->data[stack_ptr->top];
    stack_ptr->top--;
    return true;
}

bool stack_peek( stack_t* stack_ptr, int32_t* value )
{
    if ( stack_ptr == NULL || value == NULL)
    {
        return false;
    }

    if ( stack_is_empty(stack_ptr) )
    {
        return false;
    }
    *value = stack_ptr->data[stack_ptr->top];
    return true;
}

bool stack_is_empty( stack_t* stack_ptr )
{
    if ( stack_ptr->top < 0 )
    {
        return true;
    }
    return false;
}

bool stack_is_full( stack_t* stack_ptr )
{
    if( (stack_ptr->top) >= (STACK_SIZE - 1) )
    {
        return true;
    }
    return false;
}

bool stack_init( stack_t* stack_ptr )
{
    if (stack_ptr == NULL)
    {
        return false;
    }
    stack_ptr->top = -1;
    return true;
}

int main( void )
{
    stack_t stack;
    int32_t pop_val;

    int32_t test_arr[] = {3,5,7};

    uint32_t test_arr_len = sizeof(test_arr)/sizeof(test_arr[0]);
    
    // init stack 
    if ( !stack_init(&stack) )
    {
        printf("stack init fail\n");
        return -1;
    }
    printf("stack init success\n");

    // push values
    for(uint32_t i=0; i<test_arr_len; i++)
    {
        if( stack_push(&stack, test_arr[i]) )
        {
            printf("success. pushed: %d\n", test_arr[i]);
        }
        else
        {
            printf("push failed.");
            return -1;
        }
    }
    
    // pop values
    for(uint32_t j=0; j<test_arr_len; j++)
    {
        if( stack_pop(&stack, &pop_val) )
        {
            printf("popped value: %d\n", pop_val);
        }
        else
        {
            printf("pop failed.");
            return -1;
        }
    }

    // after popping all elements - stack should be empty
    if( stack_is_empty(&stack) )
    {
        printf("Stack is empty\n");
    }

    return 0;
}