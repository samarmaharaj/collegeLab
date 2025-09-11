print("This program allow user to perform arithmetic  operation by choice. \n")
result = 0
print("""
1) Addtion
2) Subtraction
3) Multiplication
4) division
5) Exponent
6) Remainder
""")

n = int(input("Choose arithmetic operation to perform: "))

if ( n == 1):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter another number to add : "))
    result = num1 + num2
    print("The sum of {0} and {1} is : {2}".format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?. ")

elif ( n == 2):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter another number to subract : "))
    result = num1 - num2
    print('The subtraction of {1} from {0} is : {2}'.format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?. ")

elif ( n == 3):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter another number to multiply : "))
    result = num1 * num2
    print('The multiplication of {0} and {1} is : {2}'.format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?. ")

elif ( n == 4 ):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter another number to divide : "))
    result = num1 / num2
    print('The division of {0} by {1} is : {2}'.format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?. ")

elif ( n == 5 ):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter power : "))
    result = num1 ** num2
    print('The {0} raised to the power of {1} is : {2}'.format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?. ")

elif ( n == 6 ):
    num1 = float(input("Enter a number : "))
    num2 = float(input("Enter a divider : "))
    result = num1 % num2
    print('The remainder when {0} is divided by {1} is : {2}'.format(num1,num2,result))
    y = input("Do you want to continue (Yes/No) (Y/N)?.  ")
else:
    print("Oops! you have enterd the wrong value. PLease try again. \n\n")
    y = input("Press any key to try again. \nEnter to exit.")

while( y and y!="n" and y!="N" ):
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

    if ( n==1 ):
        num = float(input("Enter number to add : "))
        result += num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    elif ( n== 2):
        num = float(input("Enter number to subtract : "))
        result -= num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    elif ( n== 3):
        num = float(input("Enter number to multiply : "))
        result *= num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    elif ( n== 4):
        num = float(input("Enter number to divide : "))
        result /= num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    elif ( n== 5):
        num = float(input("Enter number raised to power : "))
        result **= num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    elif ( n== 6):
        num = float(input("Enter divider : "))
        result %= num
        print("The result is :",result)
        y = input("Do you want to continue (Yes/No) (Y/N)?. ")
    else:
        print("The result is :",result)
        y = False
        print("Thanks for using our program.")

# print(eval(input("Enter operation : ")))