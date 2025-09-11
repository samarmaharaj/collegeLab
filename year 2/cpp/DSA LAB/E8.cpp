#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
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
        newNode->prev = newNode;
        head = newNode;
    } else {
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
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
        newNode->prev = newNode;
        head = newNode;
    } else {
        Node* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        tail->next = newNode;
        head->prev = newNode;
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
    newNode->prev = ptr;
    ptr->next->prev = newNode;
    ptr->next = newNode;
}

void deleteFront() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* tail = head->prev;
    if (head == tail) {
        head = NULL;
    } else {
        tail->next = head->next;
        head->next->prev = tail;
        head = head->next;
    }

    delete tail;
}

void deleteEnd() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* tail = head->prev;
    if (head == tail) {
        head = NULL;
    } else {
        tail->prev->next = head;
        head->prev = tail->prev;
    }

    delete tail;
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
    int count = 1;
    while (count < position && ptr->next != head) {
        ptr = ptr->next;
        count++;
    }

    if (count != position) {
        cout << "Position not found" << endl;
        return;
    }

    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;

    delete ptr;
}

int countNode() {
    if (head == NULL) {
        return 0;
    }

    Node*ptr = head;
    int count = 0;
    do {
        count++;
        ptr = ptr->next;
    } while (ptr != head);
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
}