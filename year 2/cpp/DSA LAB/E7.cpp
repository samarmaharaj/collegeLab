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
        cout << "Memory error" << endl;
        return;
    }

    newNode->data = data;
    newNode->next = head;
    head->next = newNode;
}

void insertEnd(int data) {
    Node* newNode = new Node();

    if (newNode == NULL) {
        cout << "Memory error" << endl;
        return;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    Node* ptr = head;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    ptr->next = newNode;
}

void insertAtPosition(int data, int position) {
    if (position <= 0) {
        cout << "Invalid Position" << endl;
        return;
    }

    Node* newNode = new Node();

    if (newNode == NULL) {
        cout << "Memory error" << endl;
        return;
    }

    newNode->data = data;

    if (position == 1) {
        newNode->next = head;
        head = newNode;
        return;
    }

    int count = 1;
    Node* ptr = head;
    while (ptr != NULL && count < position - 1) {
        ptr = ptr->next;
        count++;
    }

    if (ptr == NULL) {
        cout << "Position not found" << endl;
        return;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;
}

void deleteFront() {
    if (head == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* ptr = head;
    head = head->next;
    free(ptr);
}

void deleteEnd() {
    if (head == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    Node* ptr = head;

    if (ptr->next == NULL) {
        head = NULL;
        free(ptr);
        return;
    }

    Node* prev = head;
    while (ptr->next != NULL) {
        prev = ptr;
        ptr = ptr->next;
    }

    prev->next = NULL;
    free(ptr);
}

void deleteAtPosition(int position) {
    if (head == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    if (position <= 0) {
        cout << "Invalid Position" << endl;
        return;
    }

    Node* ptr = head;
    if (position == 1) {
        head = head->next;
        free(ptr);
        return;
    }

    int count = 1;
    Node* prev = head;
    while (ptr != NULL && count < position) {
        prev = ptr;
        ptr = ptr->next;
        count++;
    }

    if (ptr == NULL) {
        cout << "Position not found" << endl;
        return;
    }

    prev->next = ptr->next;
    free(ptr);
}

void display() {
    Node* ptr = head;

    if (ptr == NULL) {
        cout << "Linked list is empty" << endl;
        return;
    }

    while (ptr != NULL) {
        cout << ptr->data << "-> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
}

int countNode() {
    Node* ptr = head;
    int count = 0;

    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}