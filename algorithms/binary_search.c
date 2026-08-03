#include <stdio.h>
#include <stdint.h>

/*
 * Implement the Binary Search algorithm in C.
 * 
 * Given a sorted array of unsigned integers and a target value, write a function 
 * to search for the target in the array. If the target exists, return its index; 
 * otherwise, return -1.
 * 
 * Time Complexity required: O(log N)
 */

#define SIZE 8

int32_t binary_search( uint32_t* arr, uint32_t arr_len, uint32_t num );

int32_t binary_search( uint32_t* arr, uint32_t arr_len, uint32_t num )
{
    int32_t mid;
    int32_t left = 0;
    int32_t right = ((int32_t)arr_len - 1);

    if ( arr_len == 0 )
    {
        return -1;
    }

    while( left <= right )
    {
        // mid = (right + left)/2;

        mid = left + (right - left) / 2;  // also handle big numbers

        if ( arr[mid] == num )
        {
            return mid;
        }
        else if ( arr[mid] > num )
        {
            right = mid - 1;
        }
        // arr[mid] < num
        else
        {
            left = mid + 1;
        }
    }
    return -1;
}

int main( void )
{
    uint32_t array[SIZE] = {10,20,30,40,50,60,70,80};
    int32_t index;
    uint32_t number = 20;

    index = binary_search(array, SIZE, number);

    if ( index != -1 )
    {
        printf("The number %u is found at index = %u\n", number, index);
    }
    else
    {
        printf("Number doesn't found.\n");
    }
    return 0;
}