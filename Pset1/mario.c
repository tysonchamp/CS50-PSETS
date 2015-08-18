/**
 * mario.c
 * 
 * Soumya Mondal
 * tyson.granger181@gmail.com
 *  
 * CS50 Pset 1
 */


# include<cs50.h>
# include<stdio.h>


int main(void)
{
    // Variable for Hight
    printf("Enter the Hight: ");
    int hight = GetInt();

    // Checking the Hight for positive int input
    while (hight < 0 || hight > 23)
    {
        printf("Retry: ");
        hight = GetInt();
    }

    // Counters for forloops
    int i, j, k;

    // Variable for printing "#"
    int hash = hight - 2;

    // Variable for printing "Space"
    int space = -1;

    // Main Programming Part (printing mario)
    for (i = 0;i < hight;i++)
    {
        for (k = 0;k < hight + space;k++)
        {
            printf(" ");
        }
        --space;
        for (j = 0;j < hight - hash;j++)
        {
            printf("#");
        }
        hash--;
        printf("\n");
    }
}
