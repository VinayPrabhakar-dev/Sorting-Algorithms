import random
import string

# Generate 500 random characters and store them in a list
random_characters = [random.choice(string.ascii_lowercase) for _ in range(25000)]

# Write the random characters to a file named "input.txt"
with open("Char(25000).txt", "w") as file:
    for character in random_characters:
        file.write(f"{character}\n")

print("Random characters have been written to 'char.txt'.")
