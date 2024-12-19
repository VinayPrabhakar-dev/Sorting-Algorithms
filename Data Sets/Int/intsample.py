import random

random_numbers = [random.randint(1, 10000) for _ in range(25000)]

with open("Int(25000).txt", "w") as file:
    for number in random_numbers:
        file.write(f"{number}\n")

print("Random numbers have been written to 'int.txt'.")
