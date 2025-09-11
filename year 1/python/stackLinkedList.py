class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Stack:
    def __init__(self):
        self.head = None
        self.size = 0

    def push(self, data):
        newNode = Node(data)
        if self.head:
            newNode.next = self.head
        self.head = newNode
        self.size += 1
    
    def pop(self):
        if self.isEmpty():
            return "Stack is empty"
        
        poppedNode = self.head
        self.head = self.head.next
        self.size -= 1
        return poppedNode.data
    
    def peek(self):
        if self.isEmpty():
            return "Stack is empty"
        return self.head.data

    def isEmpty(self):
        return self.size == 0
    
    def getSize(self):
        return self.size
    
    def printStack(self):
        if self.isEmpty():
            print("Stack is empty")
            return
        
        temp = self.head
        while temp:
            print(temp.data, end="->")
            temp = temp.next
        print()

#usage
myStack = Stack()
myStack.push(1)
myStack.push(2)
myStack.push(3)
myStack.push(4)
myStack.push(5)

print("pop: ", myStack.pop())
print("peek: ", myStack.peek())
print("size: ", myStack.getSize())
print("isEmpty: ", myStack.isEmpty())
print("printStack: ")
myStack.printStack()