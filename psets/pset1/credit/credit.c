/*
    This program checks the validity of a credit card and prints which type of card it is.
    Jeet Khamar, CS50 - 26/05/2022.
*/

#include <stdio.h>
#include <stdbool.h>

long get_number();
bool check_length(long number);
bool check_sum(long number);
void card_type(long number);

int main(void)
{
    //Gets card number from the user.
    long number = get_number();

    //Checks whether the number is of valid length and whether it passes the check sum.
    if (!check_length(number) || !check_sum(number))
    {
        printf("INVALID\n");
        return 0;
    }

    //Prints out the type of card it is.
    card_type(number);
}

long get_number()
{
    long number;

    //Ensures no negative values can be entered.
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    return number;
}

bool check_length(long number)
{
    int length = 0;

    //Counts the number of digits in the number.
    while (number > 0)
    {
        number /= 10;
        length++;
    }

    //Checks whether length is 13, 15 or 16.
    if (length == 13 || length == 15 || length == 16)
    {
        return true;
    }

    return false;
}

bool check_sum(long number)
{
    long number1 = number;
    int sum1 = 0;

    //Sum for every other character from the last one.
    while (number1 > 0)
    {
        int digit = number1 % 10;
        sum1 += digit;
        number1 /= 100;
    }

    long number2 = number / 10;
    int sum2 = 0;

    //Sum for every other character * 2 from the second last one.
    while (number2 > 0)
    {
        int digit = 2 * (number2 % 10);

        //If value is greater than 9, the it needs to be broken down.
        if (digit > 9)
        {
            while (digit > 0)
            {
                int digit1 = digit % 10;
                sum2 += digit1;
                digit /= 10;
            }
            number2 /= 100;
        }
        else
        {
            sum2 += digit;
            number2 /= 100;
        }
    }

    int total = sum1 + sum2;

    //Checks whether last digit is a 0.
    if (total % 10 == 0)
    {
        return true;
    }

    return false;
}

void card_type(long number)
{
    long number1 = number;
    int length = 0;

    while (number1 > 0)
    {
        length++;
        number1 /= 10;
    }

    //Checking for AMEX.
    if (length == 15)
    {
        int digits = number / 10000000000000;
        if (digits == 34 || digits == 37)
        {
            printf("AMEX\n");
            return;
        }
    }
    //Checking for VISA or Mastercard.
    else if (length == 16)
    {
        int digits  = number / 100000000000000;
        if (digits >= 51 && digits <= 55)
        {
            printf("MASTERCARD\n");
            return;
        }
        digits /= 10;
        if (digits == 4)
        {
            printf("VISA\n");
            return;
        }
    }
    //Checking for VISA.
    else if (length == 13)
    {
        int digits = number / 1000000000000;
        if (digits == 4)
        {
            printf("VISA\n");
            return;
        }
    }

    printf("INVALID\n");
    return;
}