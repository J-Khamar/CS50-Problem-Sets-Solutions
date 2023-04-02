/*
    This program encrypts a text in the caesar way with a key provided by the user.
    Jeet Khamar, CS50 - 27/05/2022.
*/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Checks whether there are only 2 command line arguments.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Checks whether the key provided is entirely numberic.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    //Converts the key to an integer.
    int key = atoi(argv[1]);

    //Checks whether the key is positive.
    if (key < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string pt = get_string("plaintext: ");

    printf("ciphertext: ");

    //Loops through each letter and encrypts it. The if conditions make it case-sensitive.
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        if (isupper(pt[i]))
        {
            printf("%c", (((pt[i] - 65) + key) % 26) + 65);
        }
        else if (islower(pt[i]))
        {
            printf("%c", (((pt[i] - 97) + key) % 26) + 97);
        }
        else
        {
            printf("%c", pt[i]);
        }
    }

    printf("\n");
}