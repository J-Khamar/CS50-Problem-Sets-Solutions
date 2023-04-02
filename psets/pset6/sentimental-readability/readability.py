# This program evaluates the levl of text given by the user using the Coleman-Liau Index.
from cs50 import get_string

text = get_string("Text: ")
words, chars, sentences = 0, 0, 0

# Looping through the string to calculate the number of characters, words and sentences.
for char in text:
    if char == " ":
        words += 1
    if char == "." or char == "?" or char == "!":
        sentences += 1
    if char.isalpha():
        chars += 1
words += 1

# Calculating the number of characters and sentences per 100 words.
L = (chars * 100) / words
S = (sentences * 100) / words

# Calculating the index value based on the Coleman-Liau formula.
index = int(round(0.0588 * L - 0.296 * S - 15.8))

# Printing out the grade.
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")