# This program identifies valid credit cards and identifies their brand as well.
from cs50 import get_string
import sys

# Getting user input and calculating length of number.
number = get_string("Number: ")
length = len(number)
number1 = int(number)
sum = 0

# This code adds every other digit from the end of the number.
while number1 > 0:
    sum += number1 % 10
    number1 = number1 // 100

# This code adds the double of every other digit from the second to last digit.
number2 = int(number) // 10
while number2 > 0:
    temp = 2 * (number2 % 10)
    if temp > 9:
        while temp > 0:
            sum += (temp % 10)
            temp = temp // 10
        number2 = number2 // 100
    else:
        sum += temp
        number2 = number2 // 100

# This uses a checksum to validate the card.
if (sum % 10) != 0:
    print("INVALID")
    sys.exit()

# Depending on the length of the number and starting digits the card is identified.
temp = int(number[0:2])
if length == 15 and (temp == 34 or temp == 37):
    print("AMEX")
elif length == 16 and (temp >= 51 and temp <= 55):
    print("MASTERCARD")
elif (length == 16 or length == 13) and (temp // 10 == 4):
    print("VISA")
else:
    print("INVALID")