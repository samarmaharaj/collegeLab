class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class Queue:
    def __init__(self):
        self.front = None
        self.rear = None
        self.size = 0

    def enqueue(self, data):
        newNode = Node(data)
        if self.rear is None:
            self.front = self.rear = newNode
            self.size += 1
            return
        self.rear.next = newNode
        self.rear = newNode
        self.size += 1

    def dequeue(self):
        if self.isEmpty():
            return "Queue is empty"
        temp = self.front
        self.front = temp.next
        self.size -= 1
        if self.front is None:
            self.rear = None
        return temp.data
    
    def peek(self):
        if self.isEmpty():
            return "Queue is empty"
        return self.front.data
    
    def isEmpty(self):
        return self.size == 0
    
    def getSize(self):
        return self.size
    
    def printQueue(self):
        if self.isEmpty():
            print("Queue is empty")
            return
        
        temp = self.front
        while temp:
            print(temp.data, end=" <- ")
            temp = temp.next
        print("rear end")

queue = Queue()
queue.enqueue(1)
queue.enqueue(2)
queue.enqueue(3)
queue.enqueue(4)

print("dequeue: ", queue.dequeue())
print("peek: ", queue.peek())
print("size: ", queue.getSize())
print("isEmpty: ", queue.isEmpty())
queue.printQueue()