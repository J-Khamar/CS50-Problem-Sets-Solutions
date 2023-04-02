/*
    This program encrypts a text in the caesar way with a 26-letter key provided by the user.
    Jeet Khamar, CS50 - 27/05/2022.
*/

#include <cs50.h>
#include <stdio.h>
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

    int counter = 0;

    //Checks whether the key provided is entirely alphabetic.
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (islower(argv[1][i]))
        {
            argv[1][i] -= 32;
        }

        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        counter++;
    }

    //Checks whether the key is 26 characters long.
    if (counter != 26)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Checks whether any letter has been repeated in the key.
    for (int i = 0, n = strlen(argv[1]); i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    //Gets text to be encrypted from the user.
    string pt = get_string("plaintext: ");

    printf("ciphertext: ");

    //Loops through each letter and encrypts it. The if conditions make it case-sensitive.
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        //Replaces the letter with the appropraite letter from the key and coverts the case if needed.
        if (isupper(pt[i]))
        {
            printf("%c", argv[1][pt[i] - 65]);
        }
        else if (islower(pt[i]))
        {
            printf("%c", argv[1][pt[i] - 97] + 32);
        }
        else
        {
            printf("%c", pt[i]);
        }
    }

    printf("\n");
}