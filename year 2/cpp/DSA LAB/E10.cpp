#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* front = NULL;
Node* rear = NULL;

void enqueue(int data) {
    Node* newNode = new Node();

    if (newNode == NULL) {
        cout << "Queue is full" << endl;
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int dequeue() {
    if (front == NULL) {
        cout << "Queue is empty" << endl;
        return -1;
    }

    int val = front->data;
    Node* ptr = front;
    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
    }

    delete ptr;
    return val;
}

void display() {
    if (front == NULL) {
        cout << "Queue is empty" << endl;
        return;
    }

    Node* ptr = front;

    while (ptr != NULL) {
        cout << ptr->data << "<--";
        ptr = ptr->next;
    }
}

class CircularQueue {
private:
    int* queue;
    int Front;
    int Rear;
    int size;

public:
    CircularQueue(int s) : size(s) {
        queue = new int[size];
        Front = -1;
        Rear = -1;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    void enqueue(int data) {
        if (Front == (Rear + 1) % size) {
            cout << "Queue is full" << endl;
            return;
        }

        if (Front == -1) {
            Front = Rear = 0;
        } else {
            Rear = (Rear + 1) % size;
        }

        queue[Rear] = data;
    }

    void display() {
        if (Front == -1) {
            cout << "Queue is empty" << endl;
            return;
        }

        int i = Front;
        while (true) {
            cout << queue[i] << " ";
            if (i == Rear) break;
            i = (i + 1) % size;
        }
        cout << endl;
    }

    int dequeue() {
        if (Front == -1) {
            cout << "Queue is empty" << endl;
            return -1;
        }

        int val = queue[Front];
        if (Front == Rear) {
            Front = Rear = -1;
        } else {
            Front = (Front + 1) % size;
        }

        return val;
    }
};

int main() {
    CircularQueue cq(5);

    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.enqueue(40);
    cq.enqueue(50);

    cq.display(); // Output: 10 20 30 40 50

    cq.enqueue(60); // Output: Queue is full

    return 0;
}