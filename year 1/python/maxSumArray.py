print("This program print subset of given array whose sum is maximum. \n\n")

myList = [ int(x) for x in input("Enter list elements separated by space : ").split(" ")]
print(myList)

sum = 0
maxSum = max(myList)
initial = final = myList.index(maxSum)

n = len(myList)
for i in range(n):
    sum+=myList[i]
    if maxSum < sum:
        maxSum = sum
        final = i
    if sum <= 0:
        sum = 0
        initial = i + 1

if maxSum == max(myList):
    initial = final = myList.index(maxSum)

print("The max sum of the subset of the array is :", maxSum)
print("\nFrom {0} element to {1}. And the subset is {2}".format(initial + 1, final + 1, myList[initial:final+1]))
