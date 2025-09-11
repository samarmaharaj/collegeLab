class Node:
    def __init__(self, data):
        self.data = data;
        self.next = None

node1 = Node(10)
node2 = Node(15)
newNode1 = Node(16)
node3 = Node(20)
node4 = Node(25)
node5 = Node(30)

node1.next = node2
node2.next = newNode1
newNode1.next = node3
node3.next = node4
node4.next = node5

current_node = node1

while current_node:
    print(current_node.data, end=" -> ")
    current_node = current_node.next

print("Null")