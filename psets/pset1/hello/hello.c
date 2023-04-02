/*
    This program greets the user by their name.
    Jeet Khamar, CS50 - 26/05/2022.
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Asks user for their name as input.
    string answer = get_string("What's your name? ");
    //Greets the user by name.
    printf("hello, %s\n", answer);

    return 0;
}