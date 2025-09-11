print("This program count the number of upper and lower case letter in a given string. \n\n")

str = input("Enter the string : ")
upper = 0
lower = 0

for i in str:
    if i.isupper():
        upper += 1
    elif i.islower():
        lower += 1

print("The number of upper case letter in the given string is : ", upper)
print("The number of lower case letter in the given string is : ", lower)