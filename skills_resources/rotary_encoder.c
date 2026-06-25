#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/*
A/B Signal State Machine
------------------------
CW    CCW
----------
A B  | A B
----------
0 0  | 0 0
1 0  | 0 1
1 1  | 1 1
0 1  | 1 0
0 0  | 0 0
*/

// State transition sequences:

// CW (Clockwise):
// 00 -> 10 -> 11 -> 01 -> 00

// CCW (Counter-Clockwise):
// 00 -> 01 -> 11 -> 10 -> 00

typedef enum
{
    CW,
    CCW,
    UNDEFINED
} MOVE_DIR;

MOVE_DIR rotary_encoder( uint8_t a, uint8_t b )
{
    static uint8_t      last_state;
    uint8_t             current_state;
    uint8_t             transition_state;
    static bool         init_flag = false;
    MOVE_DIR            dir = UNDEFINED;

    if ( !init_flag )
    {
        last_state = ((a<<1)|b);
        init_flag = true;
        return UNDEFINED;
    }

    current_state = ((a<<1)|b);
    transition_state = (last_state<<2) | current_state;

    switch(transition_state)
    {
        case 0b0010:
        case 0b1011:
        case 0b1101:
        case 0b0100:
            dir = CW;
            break;
        
        case 0b0001:
        case 0b0111:
        case 0b1110:
        case 0b1000:
            dir = CCW;
            break;

        default:
            dir = UNDEFINED;
            break;
    }
    last_state = current_state;
    return dir;
}

void print_rotary_direction( MOVE_DIR dir )
{
    switch(dir)
    {
        case CW:
            printf("Moving in clock-wise direction\n");
            break;
        case CCW:
            printf("Moving in counter clock-wise direction\n");
            break;
        default:
            printf("Moving direction is undefined\n");
            break;
    }
}

int main( void )
{
    MOVE_DIR move_dir;

    move_dir = rotary_encoder( 0, 1);
    print_rotary_direction(move_dir);
    
    move_dir = rotary_encoder( 1, 1);
    print_rotary_direction(move_dir);

    return 0;
}