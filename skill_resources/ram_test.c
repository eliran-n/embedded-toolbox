#include <stdbool.h>
#include <stdint.h>

/*
 * Problem:
 * Given a 32-bit memory data word, determine whether the block is repairable.
 *
 * The input word contains fault indicators:
 * - Bits 0-4, 9-10: Non-repairable blocks. Any fault in these bits makes the
 *   block non-repairable.
 * - Bits 5-8: Memory Group #1. A group is repairable if there is at most one
 *   faulty bit and the corresponding spare block (bit 11) is available.
 * - Bits 12-16: Memory Group #2. A group is repairable if there is at most one
 *   faulty bit and the corresponding spare block (bit 17) is available.
 *
 * Algorithm:
 * 1. Check non-repairable bits using a mask.
 * 2. Count faulty bits in each repairable memory group.
 * 3. If a group contains more than one faulty bit, or a single fault without
 *    an available spare block, the memory block is considered non-repairable.
 *
 * Return:
 * true  - if the memory block can be repaired.
 * false - otherwise.
 */

// 12  11 10 9 8  7 6 5 4  3 2 1 0
//  0   0  1 1 0  0 0 0 1  1 1 1 1   
// ----------------------------------    
//         6          1    F  
// 0x0000061F
// masking to check if non repairable bits are 1

// 12   11 10 9 8   7 6 5 4   3 2 1 0
//  0   1  0  0 0   0 0 0 0   0 0 0 0 
// ----------------------------------
//  0     8             0        0
// = 0x00000800  ( masking to check if bit 11 is not faulty- spare bit )

// 19 18 17 16   15 14 13 12   11 10 9 8     7  6  5  4    3  2  1  0
//  0  0  1  0    0  0  0  0   0  0  0 0    0  0  0  0    0  0  0  0
// -------------------------------------------------------------------
//       2            0            0              0             0
// 0x00020000  ( masking to check bit 17 is not faulty - spare bit )

bool data_word_is_repairable( uint32_t data_word )
{
    uint32_t temp_dw;
    uint32_t counter = 0;

    // check the non repairable block ( if even one bit is on - word is not repairable )
    if ( (data_word & 0X0000061F) != 0 )
    {
        return false;
    }

    // move to bit index number 5
    temp_dw = data_word >> 5;

    // memory group 1 (5-8) 
    for (uint32_t i = 0; i<4; i++)
    {
        if ( (temp_dw & 1) == 1 )
        {
            counter++;
        }
        temp_dw = temp_dw >> 1;
    }

    if ( counter > 1 || ((counter == 1) && (data_word & 0x00000800) != 0) )
    {
        return false;
    }

    temp_dw = data_word >> 12;

    counter = 0;
    // memory group 2 (12-16)
    for (uint32_t i=0; i<5; i++)
    {
        if ( (temp_dw & 1) == 1 )
        {
            counter++;
        }
        temp_dw = temp_dw >> 1;
    }

    if ( counter > 1 || ((counter == 1) && (data_word & 0x00020000) != 0) )
    {
        return false;
    }

    return true;
}
