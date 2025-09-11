print("This program reverse a list. \n\n")

myList = [1, 2, 3, 4, 5, 6, 7]
print(myList)
n = len(myList)
for i in range(n//2):
    myList[i], myList[n-1-i] = myList[n-1-i], myList[i]

print(myList)