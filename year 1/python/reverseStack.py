print("This program reverses a stack. \n\n")

# Implement stack class
class Stack:
    def __init__(self):
        self.stack = []

    def push(self, item):
        self.stack.append(item)

    def pop(self):
        if not self.is_empty():
            return self.stack.pop()
        else:
            return None

    def is_empty(self):
        return len(self.stack) == 0

    def size(self):
        return len(self.stack)

# Create a stack
stack = Stack()

# Push elements to the stack
stack.push(1)
stack.push(2)
stack.push(3)
stack.push(4)
stack.push(5)

print("Original stack:", stack.stack)

# Reverse the stack
stack.stack.reverse()

# Print the reversed stack
print("Reversed stack:", stack.stack)
