/**
 * vigenere.c
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
        string text;
        int key_len = strlen(key);
        int keyar[key_len];
        int count = 0;
        int n;
        
        
        // Check if the input is alphabate and encrypt the user's text
        for (int k = 0; k < key_len; k++)
        {
            // Check if input command line arg is alphabate else return 1
            if (!isalpha(argv[1][k]))
            {
            
                printf("You entered illigal key\n");
                return 1;
            
            }
        }
        
        // Creating an arrey for the key and store as intiger
        // Starting from A = 0 to Z = 25 
        for (int j = 0; j < key_len; j++)
        {
            keyar[j] = toupper(key[j]) - 65;
        }
        
           
        // Ask to enter the text and store the string lenth in a int variable
        text = GetString();
        n = strlen(text);
           
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
                    printf("%c", ((((text[i] - 97) + keyar[count]) % 26) + 97));
                   
                    if (count < key_len - 1)
                    {
                        count++;
                    }else
                    {
                        count = 0;
                    }
                }else
                {
                    // Encrypting Capital Letters
                    printf("%c", ((((text[i] - 65) + keyar[count]) % 26) + 65));
                   
                    if (count < key_len - 1)
                    {
                        count++;
                    }else
                    {
                        count = 0;
                    }                    
                }
           
            }
           
        }
       
        printf("\n");
        return 0;
    
    }else
    {
        
        printf("Usage: ./vigenere <key>\n");
        return 1;
        
    }
    
}
