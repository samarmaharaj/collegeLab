print("This program print the linked List according to user input. \n\n")

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, data):
        newNode = Node(data)
        if self.head:
            newNode.next = self.head
        self.head = newNode
    
    # def (self):
    #     if self.isEmpty():
    #         return "Stack is empty"
        
    #     poppedNode = self.head
    #     self.head = self.head.next
    #     self.size -= 1
    #     return poppedNode.data

    # def isEmpty(self):
    #     return self.size == 0
    
    def printLinkedList(self):
        print("Null <--", end=" ")
        currentNode = self.head
        while currentNode:
            print(currentNode.data, end=" <-- ")
            currentNode = currentNode.next
        print("Head")

node = LinkedList()
n = int(input("Enter number of items to add: "))
for i in range(n):
    a = int(input("Enter {} item: ".format(i + 1)))
    node.insert(a)

node.printLinkedList()

# node1 = Node(1)
# node2 = Node(2)
# node3 = Node(3)

# node1.next = node2
# node2.next = node3

