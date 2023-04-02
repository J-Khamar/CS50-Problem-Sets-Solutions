# This program calculates the minimum number of coins required to provide change given by the user.

from cs50 import get_float

# Checks whetehr user has inputted a non negative floating point value.
while True:
    change = 100 * get_float("Change owed: ")
    if change >= 0:
        break

coins = 0

while change > 0:
    # Adds larger coin till possible the tries the next best coin till possible.
    if change >= 25:
        temp = change // 25
        coins += (temp)
        change -= (temp * 25)
    elif change >= 10:
        temp = change // 10
        coins += (temp)
        change -= (temp * 10)
    elif change >= 5:
        temp = change // 5
        coins += (temp)
        change -= (temp * 5)
    else:
        temp = change // 1
        coins += (temp)
        change -= (temp * 1)

# The coins variable needs to be converted to an integer.
print(int(coins))
