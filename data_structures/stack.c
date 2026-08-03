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

bool stack_validate_palindrome( uint32_t number, stack_t* stack )
{
    uint32_t num_len = 0;
    uint32_t lsb_digit;
    uint32_t temp = number;
    uint32_t divider;
    uint32_t next_digit;
    int32_t popped_val;

    // counter num of digits
    while( temp )
    {
        temp = temp/10;
        num_len++;
    }

    // push half digits to the stack
    temp = number;    
    for (uint32_t i=0; i<(num_len/2); i++)
    {
        lsb_digit = temp % 10;
        stack_push(stack, lsb_digit);
        temp = temp/10;
    }

    // skip on the middle value in case of odd number
    if ( num_len % 2 !=0 )
    {
        temp = temp/10;
    }
    
    // compare digits
    for (uint32_t j=0; j<(num_len/2); j++)
    {
        stack_pop(stack, &popped_val);

        next_digit = temp % 10;

        if ( next_digit != popped_val )
        {
            return false;
        }
        temp = temp/10;
    }
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