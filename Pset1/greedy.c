/**
 * greedy.c
 * 
 * Soumya Mondal
 * tyson.granger181@gmail.com
 * 
 * CS50 Pset 1
 */


# include<stdio.h>
# include<cs50.h>
# include<math.h>


int main(void)
{
    // Ask user for a input and verify if input is positive
    printf("How much change is owed?\n");
    float user_input = GetFloat();
    while(user_input < 0)
    {
        printf("How much change is owed?\n");
        user_input = GetFloat();
    }
    
    // Variables for storing calculation results
    int tfiveps, tenps, fiveps, paisa, tempvalues;
    // int total_coins = 0;
    
    // Conversion from floating point to int as cents
    float x = round(user_input * 100);
    paisa = (int) x;
    
    // counting Quarters
    tfiveps = paisa / 25;
    tempvalues = paisa % 25;
    
    // Counting Dimes & Nickles
    if (tfiveps == 0)
    {
        tenps = paisa / 10;
        tempvalues = paisa % 10;
    
        fiveps = tempvalues / 5;
        tempvalues = tempvalues % 5;
    }else if (tfiveps > 0)
    {
        tenps = tempvalues / 10;
        tempvalues = tempvalues % 10;
    
        fiveps = tempvalues / 5;
        tempvalues = tempvalues % 5;    
    }

    // coins counting
    printf("%d\n", tfiveps + tenps + fiveps + tempvalues);
}
