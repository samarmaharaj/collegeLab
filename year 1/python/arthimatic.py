print("This program perform all arithmetic operation on two values \n\n")

num1 = int(input("Enter a number : "))
num2 = int(input("Enter another number : "))

#print("The sum of", num1, "and", num2,"is :", num1 + num2)
# print(f"The sum of {num1} and {num2} is : {num1 + num2}")
# print(f"The subtraction of {num1} and {num2} is : {num1 - num2}")
# print(f"The multiplication of {num1} and {num2} is : {num1 * num2}")
# print(f"The division of {num1} and {num2} is : {num1 / num2}")
# print(f"The {num1} raised to the power {num2} is : {num1 ** num2}")
print("\n\n")
print("The sum of {0} and {1} is : {2}".format(num1,num2,num1 + num2))
print('The subtraction of {0} from {1} is : {2}'.format(num1,num2,num1 - num2))
print('The multiplication of {0} and {1} is : {2}'.format(num1,num2,num1 * num2))
print('The division of {0} by {1} is : {2}'.format(num1,num2,num1 / num2))
print('The floor division of {0} by {1} is : {2:.3f}'.format(num1,num2,num1 // num2))
print('The {0} raised to the power of {1} is : {2}'.format(num1,num2,num1 ** num2))
print('The remainder when {0} is divided by {1} is : {2}'.format(num1,num2,num1 % num2))



#print(eval(input("Enter expression : ")))