/*
    This program outputs a mario pyramid of desired size.
    Jeet Khamar, CS50 - 26/05/2022.
*/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    //Verifying whether the user input is within 1 and 8.
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //This loop iterates for every row in the pyramid.
    for (int i = 1; i <= height; i++)
    {
        //This loop prints the number of spaces in a particular line.
        for (int space = height - i; space > 0; space--)
        {
            printf(" ");
        }

        //This loop prints the number of hashes in a particular line.
        for (int hash = 1; hash <= i; hash++)
        {
            printf("#");
        }

        //This moves the cursor to the next line after the row printing is complete.
        printf("\n");
    }
}