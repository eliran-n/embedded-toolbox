#include <stdint.h>
#include <stdio.h>

// [21,20,30, 40]

// [21, 20]  2 numbers with 1 common number 2
// [20,30,40] 3 number with 3 common number 0

// the answer is 3 becasuse there are 3 nubmers

/*
 * Problem Statement:
 * Given an array of positive two-digit integers, find the maximum number of elements
 * in the array that share at least one common digit.
 *
 * Example:
 * Input:  arr = {21, 20, 30, 70}
 * Output: 3
 * Explanation: The digit '0' appears in 3 numbers (20, 30, 70), which is the maximum.
 *
 * Time Complexity:  O(n)
 * Space Complexity: O(1)
 */

uint32_t max_elements_with_common_digit(uint32_t* arr, uint32_t arr_len)
{
    uint32_t counter_digits[10] = {0};
    uint32_t first_digit;
    uint32_t last_digit;

    uint32_t max_common = 0;
    for(uint32_t i=0; i<arr_len; i++)
    {
        first_digit = arr[i]/10;
        last_digit = arr[i]%10;

        counter_digits[first_digit]++;

        // only if the last digit different from the first increment it
        if (first_digit != last_digit)
        {
            counter_digits[last_digit]++;
        }

        if (counter_digits[first_digit] > max_common)
        {
            max_common = counter_digits[first_digit];
        }
        if (counter_digits[last_digit]>max_common)
        {
            max_common = counter_digits[last_digit];
        }
    }
    return max_common;
}

int main(void)
{
    uint32_t test_arr[] = {21,20,30,70};
    uint32_t arr_len = sizeof(test_arr)/sizeof(test_arr[0]);
    uint32_t res =  max_elements_with_common_digit(test_arr, arr_len);
    printf("max common digits: %u\n", res);

    return 0;
}