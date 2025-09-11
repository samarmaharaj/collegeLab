class Queue:
    def __init__(self):
        self.queue = []

    def enqueue(self, item):
        self.queue.append(item)

    def dequeue(self):
        if self.isEmpty():
            return "UnderFlow: Stack is Empty!"
        return self.queue.pop(0)

    def peek(self):
        if self.isEmpty():
            return "Stack is Empty!"
        return self.queue[0]
    
    def isEmpty(self):
        return len(self.queue) == 0
    
    def size(self):
        return len(self.queue)
    
queue = Queue()
queue.enqueue('A')
queue.enqueue('S')
queue.enqueue('A')
queue.enqueue('M')
queue.enqueue('A')
queue.enqueue('R')

print("Queue: ", queue.queue)
print("Dequeue: ", queue.dequeue())
print("peek: ", queue.peek())
print("isEmpty: ", queue.isEmpty())
print("Size: ", queue.size())
    