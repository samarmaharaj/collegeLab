#include <bits/stdc++.h>
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
    head = newNode;
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

    while (ptr->next != NULL) {
        cout << ptr->data << "-> ";
        ptr = ptr->next;
    }

    cout << ptr->data << "-> NULL" << endl;
}

int main() {
    int choice;

    do {
        cout << "Menu:" << endl;
        cout << "1. Insert element at the front of linked list." << endl;
        cout << "2. Insert a node at the end of the Linked list." << endl;
        cout << "3. Insert a node at given position." << endl;
        cout << "4. Delete element from the front of linked list." << endl;
        cout << "5. Delete element from the end of linked list." << endl;
        cout << "6. Delete a node at given position." << endl;
        cout << "7. Display elements" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                int data;
                cout << "Enter data: ";
                cin >> data;
                insertFront(data);

                cout << "Inserted successfully!" << endl;
                break;
            case 2:
                int data2;
                cout << "Enter data: ";
                cin >> data2;
                insertEnd(data2);

                cout << "Inserted successfully!" << endl;
                break;
            case 3:
                int data3, key;
                cout << "Enter data: ";
                cin >> data3;
                cout << "Enter position at which you want to insert: " << endl;
                cin >> key;

                insertAtPosition(data3, key);

                cout << "Inserted successfully!" << endl;
                break;
            case 4:
                deleteFront();

                cout << "First element is successfully deleted!" << endl;
                break;
            case 5:
                deleteEnd();

                cout << "Last element is successfully deleted!" << endl;
                break;
            case 6:
                int key2;
                cout << "Enter position at which you want to delete: " << endl;
                cin >> key2;

                deleteAtPosition(key2);

                cout << "Deleted successfully!" << endl;
                break;
            case 7:
                display();
                break;
            case 8:
                break;
        }
    } while (choice != 8);
}