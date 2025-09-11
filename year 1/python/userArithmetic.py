print("This program allow user to perform arithmetic  operation by choice. \n")
y = True
while(y and y!="n" and y!="N"):
    print("""
    1) Addtion
    2) Subtraction
    3) Multiplication
    4) division
    5) Exponent
    6) Remainder
    7) Exit or any random input
    """)

    n = int(input("Choose arithmetic operation to perform: "))

    if ( n == 1):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter another number to add : "))
        print("The sum of {0} and {1} is : {2}".format(num1,num2,num1 + num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit.")

    elif ( n == 2):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter another number to subract : "))
        print('The subtraction of {1} from {0} is : {2}'.format(num1,num2,num1 - num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit.")

    elif ( n == 3):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter another number to multiply : "))
        print('The multiplication of {0} and {1} is : {2}'.format(num1,num2,num1 * num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit.")

    elif ( n == 4 ):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter another number to divide : "))
        print('The division of {0} by {1} is : {2}'.format(num1,num2,num1 / num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit.")

    elif ( n == 5 ):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter power : "))
        print('The {0} raised to the power of {1} is : {2}'.format(num1,num2,num1 ** num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit.")

    elif ( n == 6 ):
        num1 = float(input("Enter a number : "))
        num2 = float(input("Enter a divider : "))
        print('The remainder when {0} is divided by {1} is : {2}'.format(num1,num2,num1 % num2))
        y = input("Do you want to continue (Yes/No) (Y/N)?. \nPress Enter to exit. ")

    elif ( n == 7 ):
        break
    else:
        print("Oops! you have enterd the wrong value. PLease try again. \n\n")
        y = input("Press any key to try again. \nEnter to exit.")

print("Thanks for using our program.")

# print(eval(input("Enter operation : ")))