/**
 * caesar.c
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
#include <stdlib.h>


int main(int argc, string argv[])
{
    
    if (argc == 2)
    {
        
        // Variable declaration
        string key = argv[1];
        string text = GetString();
        int i_key = atoi(key), n = strlen(text);
        
        // Encrypting The Text with the Key
        for (int i = 0; i < n; i++)
        {
            // Check if the Character is Alphabate if not print the same
            if (!isalpha(text[i]))
            {
                printf("%c", text[i]);
            }else
            {
                // Encrypt All the Characters
                if (islower(text[i]))
                {
                    // Encrypting Small Characters
                    printf("%c", ((((text[i] - 97) + i_key) % 26) + 97));
                    
                }else
                {
                    // Encrypting Capital Letters
                    printf("%c", ((((text[i] - 65) + i_key) % 26) + 65));
                
                }
            
            }
            
        }
        
        printf("\n");
        return 0;
        
    }else
    {
        
        printf("Usage: ./caesar <key>\n");
        return 1;
        
    }
    
}
