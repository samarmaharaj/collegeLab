print("This program swap two variable witout using third variable \n\n")

num1 = float(input("Enter a number : "))
num2 = float(input("Enter another number : "))

print("The two number: number 1 = {0} and number 2 = {1}".format(num1, num2))

# num2 = num1 + num2
# num1 = num2 - num1
# num2 = num2 - num1

num1, num2 = num2, num1

print("After Swapping:")
print("The two number: number 1 = {0} and number 2 = {1}".format(num1, num2))