#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void insertFront(int data) {
    Node* newNode = new Node();

    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    
    newNode->data = data;

    if (head == NULL) {
        newNode->next = newNode;
        head = newNode;
    } else {
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        newNode->next = head;
        tail->next = newNode;
        head = newNode;
    }
}

void insertEnd(int data) {
    Node* newNode = new Node();
    
    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    
    newNode->data = data;

    if (head == NULL) {
        newNode->next = newNode;
        head = newNode;
    } else {
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        newNode->next = head;
        tail->next = newNode;
    }
}

void insertAtPosition(int data, int position) {
    if (position <= 0) {
        cout << "Invalid position" << endl;
        return;
    }

    if (position == 1) {
        insertFront(data);
        return;
    }

    Node* newNode = new Node();
    
    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    
    newNode->data = data;

    Node* ptr = head;
    int count = 1;
    while (count < position - 1 && ptr->next != head) {
        ptr = ptr->next;
        count++;
    }

    if (count != position - 1) {
        cout << "Position not found" << endl;
        delete newNode;
        return;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;
}

void deleteFront() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* tail = head;
    while (tail->next != head) {
        tail = tail->next;
    }

    if (head == tail) {
        delete head;
        head = NULL;
    } else {
        Node* temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
    }
}

void deleteEnd() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* tail = head;
    Node* prev = NULL;
    while (tail->next != head) {
        prev = tail;
        tail = tail->next;
    }

    if (head == tail) {
        delete head;
        head = NULL;
    } else {
        prev->next = head;
        delete tail;
    }
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    if (position <= 0) {
        cout << "Invalid position" << endl;
        return;
    }

    if (position == 1) {
        deleteFront();
        return;
    }

    Node* ptr = head;
    Node* prev = NULL;
    int count = 1;
    while (count < position && ptr->next != head) {
        prev = ptr;
        ptr = ptr->next;
        count++;
    }

    if (count != position) {
        cout << "Position not found" << endl;
        return;
    }

    prev->next = ptr->next;
    delete ptr;
}

int countNode() {
    if (head == NULL) {
        return 0;
    }

    Node* ptr = head;
    int count = 0;
    do {
        count++;
        ptr = ptr->next;
    } while (ptr != head);
    return count;
}
    
void display() {
    if (head == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* ptr = head;
    do {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    } while (ptr != head);
    cout << "HEAD" << endl;
}