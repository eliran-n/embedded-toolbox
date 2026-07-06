#include <stdint.h>
#include <stdio.h>

// Reverses only uppercase letters in the string while keeping their positions 
// relative to lowercase letters unchanged.
// Uses two-pointer approach from both ends of the string.

/* Example:
0 1 2 3 4
---------
a B n C F
---------
a F n C B
*/

char* reverse_capital_letters( char* str, uint32_t str_len )
{
    uint32_t i = 0;
    uint32_t j = str_len - 1;
    char temp;

    while (i<j)
    { 
        if ( (str[i] >= 'A' && str[i] <= 'Z') && (str[j] >= 'A' && str[j] <= 'Z') )
        {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            i++;
            j--;
        }
        else if ( (str[i] >= 'A' && str[i] <= 'Z') )
        {
            j--;
        }
        else if ( (str[j] >= 'A' && str[j] <= 'Z') )
        {
            i++;
        }
        else
        {   
            i++;
            j--;
        }
    }

    return str;
}


int main( void )
{
    char str_test[] = "aBnCF";

    reverse_capital_letters(str_test, sizeof(str_test));

    printf("Reversed string: %s", str_test);

    return 0;
}