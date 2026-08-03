#include <stdbool.h>
#include <stdint.h>

uint8_t string_len( char* str )
{
    uint8_t len = 0;

    while(*str)
    {
        len++;
        str++;
    }
    return len;
}

bool string_check_permutation_ver1( char* str1, char* str2 )
{
    uint8_t hash_table[256] = {0};
    uint8_t str1_len = 0;
    uint8_t str2_len = 0;

    str1_len = string_len( str1 );
    str2_len = string_len( str2 );
    
    if ( str1_len != str2_len )
    {
        return false;
    }

    for( uint8_t i=0; i<str1_len; i++)
    {
        hash_table[str1[i]]++;
        hash_table[str2[i]]--;
    }

    // consider as O(1) since we running 256 times
    for(uint8_t j=0; j<256; j++)
    {
        if ( hash_table[j] != 0 )
        {
            return false;
        }
    }
    return true;
}

bool string_check_permutation_ver2( char* str1, char* str2 )
{
    uint8_t hash_table1[256] = {0};
    uint8_t hash_table2[256] = {0};

    uint8_t str1_len = 0;
    uint8_t str2_len = 0;

    str1_len = string_len( str1 );
    str2_len = string_len( str2 );
    
    if ( str1_len != str2_len )
    {
        return false;
    }

    for( uint8_t i=0; i<str1_len; i++)
    {
        hash_table1[str1[i]]++;
        hash_table2[str2[i]]++;
    }

    // consider as O(1) since we running 256 times
    for(uint8_t j=0; j<256; j++)
    {
        if ( hash_table1[j] != hash_table2[j] )
        {
            return false;
        }
    }
    return true;
}


int main( void )
{
    return 0;
}