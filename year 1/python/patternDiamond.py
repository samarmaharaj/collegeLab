print("This program print diamond pattern. \n\n")

n = int(input("Enter number of row : "))

for i in range(n, 0, -1):
    for j in range(i):
        print("*", end=" ")
    for j in range(i, n):
        print("   ",end=" ")
    for j in range(i):
        print("*", end=" ")
    print()
for i in range(2, n+1):
    for j in range(i):
        print("*", end=" ")
    for j in range(i, n):
        print("   ",end=" ")
    for j in range(i):
        print("*", end=" ")
    print()