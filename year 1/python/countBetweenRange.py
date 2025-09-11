print("This program print the number of positive numbers inside a list. \n\n")

myList = [ int(x) for x in input("Enter elements of list separated by space : ").split(" ")]
print(myList)

ran = [ int(x) for x in input("Enter range separated by space : ").split(" ")]

#To check if they have entered only two number
while (len(ran) != 2):
    ran = [ int(x) for x in input("Please enter only two number : ").split(" ")]

#If they entered range in reverse order
if ran[0] > ran[1]:
    ran[0], ran[1] = ran[1], ran[0]
print(ran)

count = 0
for x in myList:
    if x >= ran[0] and x <= ran[1] and x > 0:
        count += 1

print("The number of positive number in the given list from {0} to {1} is : {2}".format(ran[0], ran[1], count))