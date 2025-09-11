print("This program print the elements which appeared maximum times in the list.\n\n")

# myList = [1, 2, 3, 1, 4, 6, 7, 6, 5, 7, 3, 2, 3, 4, 1, 6, 9, 7]
myList = [ int(x) for x in input("Enter elements of list separated by space : ").split(" ")]
print(myList)

myDict = {}

for i in range(len(myList)):
    if myList[i] in myDict.keys():
        myDict[myList[i]] += 1
    else:
        myDict[myList[i]] = 1

print(myDict)
max = 1
for x in myDict.values():
    if max < x:
        max = x
    
# print(max)

print("The maximum times number appeared are : ")
for i in myDict:
    if myDict[i] == max:
        print("Number {0} appeared {1} times.".format(i, myDict[i]))
