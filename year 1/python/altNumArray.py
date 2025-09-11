print("Write a program to rearange the array elements in alternating positive and negative items. Without using space.\n\n")
myList = [-1, 2, 9, -3, 4, -3, 8]
i = 0
while i < len(myList):
    if (i % 2 == 0 and myList[i] < 0) or (i % 2 != 0 and myList[i] > 0):
        j = i + 1
        while j < len(myList):
            if (i % 2 == 0 and myList[j] > 0) or (i % 2 != 0 and myList[j] < 0):
                break
            j += 1
        if j < len(myList):
            myList[i], myList[j] = myList[j], myList[i]
    i += 1

print(myList)
# # 
# # myList = [1, 2, 3, 4, -1, -2, -3, -4]
# # p = []
# # n = []
# # z = []
# # for i in range(len(myList)):
# #     if i > 0:
# #         p.append(myList[i])
# #     if i < 0:
# #         n.append(myList[i])
# #     else:
# #         z.append(myList[i])

# # new = []
# # for i in range(len(myList)):
# #     if i%2 == 0:
# #         new.append(p[i//2])
# #     if i%2 != 0:
# #         new.append(n[i//2])

# # print(new)
# myList = [-1, 2, 9, -3, 4, -3]
# # for i in range(len(myList)):
# #     if i%2 == 0:
# #         while(myList[i] < 0):
# #             for j in range(i, len(myList)):
# #                 myList[i], myList[i+1] = myList[i+1], myList[i]
# #     if i%2 != 0:
# #         while(myList[i] > 0):
# #             for j in range(i, len(myList)):
# #                 myList[i], myList[i+1] = myList[i+1], myList[i]
# p = []
# n = []
# for i in range(len(myList)):
#     if myList[i] > 0:
#         p.append(myList[i])
#     if myList[i] < 0:
#         n.append(myList[i])

# print(myList)

# for i in range(len(myList)):
#     if ( p[i//2] and n[(i-1)//2]):
#         if i%2 == 0:
#             myList[i] = p[i//2]
#         else:
#             myList[i] = n[(i-1)//2]
#     else:
#         if len(p)> len(n):
#             myList[i] = p[i]
    
# print(myList)