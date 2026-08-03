#include <stdio.h>
#include <stdint.h>

/*
 * Question:
 * Given an array of song durations in seconds (e.g., [60, 130, 50, 120]).
 * Count how many pairs of songs yield a total duration that is a whole number of minutes.
 * Required time complexity: O(N).
 */

// brute force solution

// Example: [50,10,30,130]

// the answer is two pairs: 50,10 and 50,130

/*
01
02
03

12
13

23
*/

// o(n^2) solution
uint32_t count_songs_pairs_brute_force( uint32_t* array, uint32_t arr_len )
{
    uint32_t counter = 0;

    for( uint32_t i=0; i<(arr_len-1); i++)
    {
        for(uint32_t j=i+1; j<arr_len; j++)
        {
            if( (array[i] + array[j]) % 60 == 0 )
            {
                counter++;
            }
        }
    }
    return counter;
}

// hash table solution

// Example: [50,10,30,130]
uint32_t count_songs_pairs_hash( uint32_t* array, uint32_t arr_len )
{
    uint32_t remainder;
    uint32_t complement;
    uint32_t hash_table[60] = {0};
    uint32_t counter = 0;

    for(uint32_t i=0; i<arr_len;i++)
    {
        remainder = array[i] % 60;
        complement = (60 - remainder) % 60;

        // if the complement of the song do exist - increment the counter with number of apperance it's present
        // and store the current number in the array as history for the next compares
        if (hash_table[complement] != 0)
        {
            counter += hash_table[complement];
            hash_table[remainder]++;
        }
        // if complement doesn't exist in the array just store the number
        else
        {
            hash_table[remainder]++;
        }
    }
    return counter;
}

int main( void )
{
    uint32_t songs_arr[] = {50, 10, 40, 20};
    uint32_t arr_len = sizeof(songs_arr)/sizeof(songs_arr[0]);
    uint32_t pairs_num = 0;

    pairs_num = count_songs_pairs_brute_force( songs_arr, arr_len );
    printf("Songs pairs (brute force): %d\n", pairs_num);

    pairs_num = count_songs_pairs_hash( songs_arr, arr_len );
    printf("Songs pairs (hash): %d\n", pairs_num);

    return 0;
}
