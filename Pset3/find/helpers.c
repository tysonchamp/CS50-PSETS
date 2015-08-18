/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Define start and end variables
    int end = n;
    int start = 0;
    
    // Binary Search Algorithm
    while(start <= end)
    {
        // initialize the middle
        int middle = (start + end) / 2;
       
        // check if value is at middle
        if (value == values[middle])
        {
            // Value is found
            return true;
        }
       
        // check if value is left of middle     
        else if(value < values[middle])
        {
            // reset end
            end = middle - 1;
        }
       
        // check if value is right of middle     
        else if(value > values[middle])
        {
            // reset start
            start = middle + 1;
        }
    }
    
    // Value is not found
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Variables diclaration
    int counter, temp;
    
    // an O(n^2) sorting algorithm
    do
    {
        // initialize counter
        counter = 0;
        
        // Shorting the arrey
        for (int i = 0; i < n; i++)
        {
            
            if (values[i] > values[i + 1])
            {
                // Swaping values
                temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                
                // Incrementing the counter
                counter++;
            }
        }
    } while ( counter > 0);

}
