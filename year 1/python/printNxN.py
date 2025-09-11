print("This program print pattern. \n\n")

n = int(input("Enter the number of stars in a row : "))

if n >= 1:
    for i in range(n):
        print("* "*n)
else:
    print("Since the number is less than 1, nothing is printed.")

# [print("* "*n) for i in range(n)] if n >= 1 else print("Since the number is less than 1, nothing is printed.")
