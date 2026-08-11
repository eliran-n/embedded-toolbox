#include <stdio.h>
#include <stdint.h>


// find the max repeated (identical) nubmers in a given array
// for example: [12, 7, 1, 4, 6, 12, 16, 12, 4]
// then the solution will be 3. since 12 is the most repeated and he repeated 3 times.

uint32_t max_repeat_elements_in_arr(int32_t* arr, uint32_t arr_len, uint32_t max_range )
{
    // direct address table 
    // the most important to understand that if the range of the numbers is known in advance
    // we can define array with fixed length and then solve the problem using direct address table
    // if the range of the numbers in the given array isn't known - we need to use hash table
    // but then we need to take are the situation where we will have collision - which means
    // the hash code value is identical for two keys and then we need to use linked list to implement 
    // it using chainning method (the data structure will be key, counter, and pointer to the next node)

    int32_t count_table[max_range];
    uint32_t i;

    // initial count table
    for (i=0; i<max_range; i++)
    {
        count_table[i] = 0;
    }

    // count repeated elements and find what is the max repeating  
    uint32_t max_repeat_cnt = 0;
    for (i=0; i<arr_len; i++)
    {
        count_table[arr[i]]++;

        if (count_table[arr[i]] > max_repeat_cnt)
        {
            max_repeat_cnt = count_table[arr[i]];
        }
    }
    return max_repeat_cnt;
}

/*
 * HASH TABLE + CHAINING SOLUTION
 *
 * When the range of possible values is unknown or too large,
 * use a Hash Table to count the occurrences of each value.
 *
 * Each bucket stores a pointer to the first Node of a linked list.
 * If two different values produce the same hash code, a collision
 * occurs, so the new value is added to the linked list of that bucket.
 *
 * Node:
 *     value   -> the actual value (key)
 *     counter -> number of occurrences
 *     next    -> pointer to the next Node in the bucket
 *
 * First pass:
 *     1. Calculate hash(value).
 *     2. Access the corresponding bucket.
 *     3. If the value already exists -> increment counter.
 *     4. If it doesn't exist -> create a new Node.
 *
 * Second pass:
 *     Traverse all buckets and all linked lists.
 *     Find the Node with the largest counter.
 *
 * Time complexity:
 *     Average: O(n)
 *     Worst case: O(n^2) if many values collide into the same bucket.
 */


/*
 * arr_ptr = pointer to an array of Node_t* (bucket heads)
 *
 *     arr_ptr
 *        |
 *        v
 *   +------+------+------+------+------+
 *   |  [0] |  [1] |  [2] |  [3] |  [4] |
 *   +------+------+------+------+------+
 *      |      |      |      |      |
 *     NULL   NULL     |     NULL   NULL
 *                     |
 *                     v
 *              +------------------+
 *              | value = 31       |
 *              | counter = 3      |
 *              | next ----------- |----+
 *              +------------------+    |
 *                                        v
 *                              +------------------+
 *                              | value = 23       |
 *                              | counter = 2      |
 *                              | next ----------- |----> NULL
 *                              +------------------+
 *
 * arr_ptr[2] points to the first Node in the bucket.
 * Each bucket can contain a linked list of Nodes.
 */

typedef struct Node
{
    uint32_t value;
    uint32_t counter;
    struct Node* next;
} Node_t;

Node_t* allocate_new_node(uint32_t value )
{
        Node_t* allocated_node = (Node_t*)malloc(sizeof(Node_t));

        if ( allocated_node == NULL )
        {
            return NULL;
        }
        allocated_node->value = value;
        allocated_node->counter = 0;
        allocated_node->next = NULL;
        return allocated_node;
}

int32_t max_repeat_elements_linked_list(int32_t* arr, uint32_t k_elemnts)
{
    uint32_t hash_code;
    uint32_t i;

    // assign the array of pointers - it will allocate in the FLASH (better if there're many elements)
    Node_t** arr_ptr = malloc(sizeof(Node_t*)*k_elemnts);

    // This is static allocation (array of pointers) - if not many element - this will allocated on the Stack
    // Node_t* arr_ptr[k_elemnts]

    // initialize the array pointers with NULL
    for (i=0; i<k_elemnts; i++)
    {
        arr_ptr[i] = NULL;
    }

    // counter each element and chaining elements in case of collision
    for(i=0; i<k_elemnts; i++)
    {
        hash_code = arr[i] % k_elemnts;

        if ( arr_ptr[hash_code] == NULL )
        {
            arr_ptr[hash_code] = allocate_new_node(arr[i]);

            if ( arr_ptr[hash_code] == NULL )
            {
                return -1;
            }
            arr_ptr[hash_code]->counter += 1;
        }
        // save value in the bucket
        else if ( arr_ptr[hash_code] != NULL && arr_ptr[hash_code]->value == arr[i] )
        {
            arr_ptr[hash_code]->counter += 1;
        }
        // collision case
        else
        {
            Node_t* current_node = arr_ptr[hash_code];

            while (current_node->next != NULL )
            {
                current_node = current_node->next;
            }
            // allocated new node
            Node_t* new_node = allocate_new_node(arr[i]);

            if ( new_node == NULL )
            {
                return -1;
            }
            // increment the counter
            new_node->counter += 1;
            // assign the address of the new node to current->next
            current_node->next = new_node;
        }
    }

    uint32_t counter = 0;
    uint32_t max_repeat_val;

    for(i=0; i<k_elemnts; i++)
    {
        if( arr_ptr[i] != NULL )
        {
            Node_t* current_node = arr_ptr[i];

            while(current_node != NULL)
            {
                if (current_node->counter > counter)
                {
                    counter = current_node->counter;
                    max_repeat_val = current_node->value;
                }
                current_node = current_node->next;
            }
        }
    }
    return max_repeat_val;
}

int main( void )
{
    return 0;
}
