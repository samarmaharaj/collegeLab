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
    newNode->next = head;
    newNode->prev = NULL;

    if (head != NULL) {
        head->prev = newNode;
    }
    
    head = newNode;
}

void insertEnd(int data) {
    Node* newNode = new Node();
    
    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = newNode;
    } else {
        Node* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = newNode;
        newNode->prev = tail;
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
    while (count < position - 1 && ptr != NULL) {
        ptr = ptr->next;
        count++;
    }

    if (ptr == NULL || count != position - 1) {
        cout << "Position not found" << endl;
        delete newNode;
        return;
    }

    newNode->next = ptr->next;
    newNode->prev = ptr;
    if (ptr->next != NULL) {
        ptr->next->prev = newNode;
    }
    ptr->next = newNode;
}

void deleteFront() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* temp = head;
    head = head->next;

    if (head != NULL) {
        head->prev = NULL;
    }

    delete temp;
}

void deleteEnd() {
    if (head == NULL) {
        cout << "Linked list is empty. Underflow." << endl;
        return;
    }

    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    if (tail->prev != NULL) {
        tail->prev->next = NULL;
    } else {
        head = NULL;
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
    while (count < position && ptr != NULL) {
        ptr = ptr->next;
        count++;
    }

    if (ptr == NULL || count != position) {
        cout << "Position not found" << endl;
        return;
    }

    if (ptr->prev != NULL) {
        ptr->prev->next = ptr->next;
    }
    if (ptr->next != NULL) {
        ptr->next->prev = ptr->prev;
    }

    delete ptr;
}

int countNode() {
    if (head == NULL) {
        return 0;
    }

    Node* ptr = head;
    int count = 0;
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}
    
void display() {
    if (head == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* ptr = head;
    while (ptr != NULL) {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
}