class Stack:
    def __init__(self):
        self.stack = []

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        if self.isEmpty():
            return "UnderFlow: Stack is Empty!"
        return self.stack.pop()

    def peek(self):
        if self.isEmpty():
            return "Stack is Empty!"
        return self.stack[-1]
    
    def isEmpty(self):
        return len(self.stack) == 0
    
    def size(self):
        return len(self.stack)
    
stack = Stack()
stack.push('S')
stack.push('A')
stack.push('M')
stack.push('A')
stack.push('R')
stack.push('K')

print("Stack: ", stack.stack)
print("Pop: ", stack.pop())
print("Peek: ", stack.peek())
print("isEmpty: ", stack.isEmpty())
print("Size: ", stack.size())
