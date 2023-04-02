# This program prints a mario pyramid of user desired size.

from cs50 import get_int

# This loop checks whether the user input is between 1 and 8.
while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break

for i in range(1, height + 1):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)