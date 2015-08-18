/**
 * initials.c
 *
 * Soumya Mondal
 * tyson.granger181@gmail.com
 *
 * CS50
 *
 * Problem Set - 2
 */


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    // Ask user for the full name
    string full_name = GetString();
    
    // Variables used in foorloops
    int n = strlen(full_name);
    
    // print the fisrt character of the name
    printf("%c", toupper(full_name[0]));
    
    // print rest of the characters of the name using loop
    for (int i = 0; i < n; i++)
    {
        
        // checking for space and print the initial character
        if (full_name[i] == ' ')
        {
            
            printf("%c", toupper(full_name[i + 1]));
            
        }
        
    }
    
    printf("\n");
    
    
    return 0;
}
