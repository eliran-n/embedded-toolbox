#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint32_t set_bit_by_position( uint32_t number, uint32_t position )
{
    number = number | (1U<<position);
    return number;
}

uint32_t clear_bit_by_position( uint32_t number, uint32_t position )
{
    number = number & ~(1U<<position);
    return number;
}

uint32_t toggle_bit_by_position( uint32_t number, uint32_t position )
{
    if ( (number & (1U<<position)) != 0 )
    {
        return clear_bit_by_position( number, position );
    }
    else
    {
        return set_bit_by_position( number, position );
    }
}

uint32_t toggle_bit_by_position_effective( uint32_t number, uint32_t position )
{
    number = number ^(1U<<position);
    return number;
}

bool check_bit_is_set( uint32_t number, uint32_t position )
{
    if ( (number & (1U<<position)) != 0 )
    {
        return true;
    }
    return false;
}

bool check_bit_is_off( uint32_t number, uint32_t position )
{
    if ( (number & (1U<<position)) == 0 )
    {
        return true;
    }
    return false;
}

uint32_t shift_left_by_n( uint32_t number, uint32_t n )
{
    number = (number << n);
    return number;
}

uint32_t shift_right_by_n( uint32_t number, uint32_t n )
{
    number = (number >> n);
    return number;
}

uint32_t multiply_by_2( uint32_t number )
{
    return shift_left_by_n( number , 1);
}

uint32_t divide_by_2( uint32_t number )
{
    return shift_right_by_n( number , 1);
}

uint32_t reverse_bits( uint32_t number )
{
    const uint32_t bit_len = 32;
    uint32_t reversed_num = 0;

    for (uint32_t i=0; i<bit_len; i++)
    {
        reversed_num = reversed_num | ( (number & 1U) << (bit_len-i-1) );
        number = number >> 1;
    }
    return reversed_num;
}

uint32_t calculate_power( uint32_t base, uint32_t power )
{
    uint32_t result = 1;

    for (uint32_t i=0; i<power; i++)
    {
        result = result*base;
    }
    return result;
}

uint32_t calculate_power_binary_exponentiation( uint32_t base, uint32_t power )
{
    uint32_t result = 1;

    while ( power != 0 )
    {
        if ( (power & 1) == 1 )
        {
            result = result * base;
        }
        base = base*base;
        power = power >> 1;
    }
    
    return result;
}

int main( void )
{
    uint32_t result;

    // 1000 -> 
    result = set_bit_by_position(8, 2);
    printf("Number 8 after setting bit at position 2: %u\n", result );

    // 1100 -> 1000
    result = clear_bit_by_position(12, 2);
    printf("Number 12 after clearing bit at position 2: %u\n", result );

    // 1000 - > 1010
    result = toggle_bit_by_position(8, 1);
    printf("Number 8 after toggling bit at position 1: %u\n", result );

    // 10100
    if ( check_bit_is_set(20, 2) == true )
    {
        printf("Bit 2 in number 20 is ON.\n");
    }
    else
    {
        printf("Bit 2 in number 20 is OFF.\n");
    }

    // 101
    if ( check_bit_is_off(5, 1) == true )
    {
        printf("Bit 1 in number 5 is OFF.\n");
    }
    else
    {
        printf("Bit 1 in number 5 is ON.\n");
    }

    result = multiply_by_2(6);
    printf("Multiply 6x2 = %u\n", result);

    result = divide_by_2(8);
    printf("Devide 8/2 = %u\n", result);
// 
    // 0000 0000 0000 0000 0000 0000 0000 0001
    // 1000 0000 0000 0000 0000 0000 0000 0000
    result = reverse_bits(1);
    printf("The reverse number of 1 is: %u\n", result);

    result = calculate_power(3, 2);
    printf("3^2 = %u\n", result);

    result = calculate_power_binary_exponentiation(3, 13);
    printf("3^5 = %u\n", result);

    return 0;
}