/*
    This program decides the reading level of a piece of text inputted by the user based on the Coleman-Liau Index.
    Jeet Khamar, CS50 - 27/05/2022.
*/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int letters = 0, words = 1, sentences = 0;

    //This calculates the amount of letters, words and sentences.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }

    //This gets the amount of letters and sentences per 100 words.
    float L = (100.0 * letters) / words;
    float S = (100.0 * sentences) / words;

    //This calculates the Coleman-Liau Index.
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    //This prints the level based on the value of the index.
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}