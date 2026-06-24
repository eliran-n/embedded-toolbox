#include <stdio.h>
#include <stdint.h>

/*
 * Problem: Climbing Stairs
 *
 * You are given N stairs.
 * You can climb either 1 step or 2 steps at a time.
 *
 * Return the number of distinct ways to reach the top.
 *
 */

/* Series description:
 * The series is based on the Fibonacci series, but for n = 0 we define the solution as 1 instead of 0.
 *
* We define it this way because to climb 0 stairs we assume there is 1 possibility:
* to do nothing.
 *
 *  0 | 1 | 2 | 3 | 4 | 5 | ...
 *  1 | 1 | 2 | 3 | 5 | 8 | ...
 */

// recursive solution -  O(2^n)
unsigned int get_climb_ways_by_n_recursive( unsigned int num )
{
    if ( num <= 1 )
    {
        return 1;
    }
    
    if ( num == 2 )
    {
        return 2;
    }

    return ( get_climb_ways_by_n_recursive(num-1) + get_climb_ways_by_n_recursive(num-2) );
}

// dynamic programming solution - O(n)
uint32_t get_climb_ways_by_n_dp( uint32_t num )
{
    uint32_t memory[32] = {0};

    memory[0] = 1;
    memory[1] = 1;

    uint32_t i;
    for (i=2; i<=num; i++)
    {
        memory[i] = memory[i-1] + memory[i-2];
    }
    return memory[num];
}

// dynamic programming solution with O(1) space complexity (Without array)
uint32_t get_climb_ways_by_n_dp_optimize( uint32_t num)
{
    uint32_t prev1 = 1;
    uint32_t prev2 = 1;

    if ( num <= 1 )
    {
        return 1;
    }

    uint32_t current = 0;

    for( uint32_t i=2; i<=num; i++)
    {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

// number
// 0 1 2 3 4 5 6 
// -------------
// value
// 1 1 2 3 5 8 13

int main( void )
{
    uint32_t res;
    
    //res = get_climb_ways_by_n_recursive(4);
    //printf("Number of cominations for n=4 -> %u\n", res);

    //res = get_climb_ways_by_n_dp(5);
    //printf("Number of cominations for n=5 -> %u\n", res);

    res= get_climb_ways_by_n_dp_optimize(5);
    printf("Number of cominations for n=5 -> %u\n", res);

    return 0;
}