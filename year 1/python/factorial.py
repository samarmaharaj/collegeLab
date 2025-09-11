print("This program print the factorial of a user input number. \n\n")

n = int(input("Enter a number whose factorial is to find: "))

def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n-1)
    
print("The factorial of {} is {}.".format(n, factorial(n)))