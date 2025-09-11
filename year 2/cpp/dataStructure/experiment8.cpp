#include <bits/stdc++.h>
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
        cout << "Invalid Position" << endl;
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

    Node* ptr = head;
    if (head->next == head) {
        head = NULL;
    } else {
        Node* tail = head->prev;
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }

    delete ptr;
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

    cout << "NULL" << endl;
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
            case 1: {
                int data;
                cout << "Enter data: ";
                cin >> data;
                insertFront(data);
                cout << "Inserted successfully!" << endl;
                break;
            }
            case 2: {
                int data;
                cout << "Enter data: ";
                cin >> data;
                insertEnd(data);
                cout << "Inserted successfully!" << endl;
                break;
            }
            case 3: {
                int data, position;
                cout << "Enter data: ";
                cin >> data;
                cout << "Enter position at which you want to insert: ";
                cin >> position;
                insertAtPosition(data, position);
                cout << "Inserted successfully!" << endl;
                break;
            }
            case 4:
                deleteFront();
                cout << "First element is successfully deleted!" << endl;
                break;
            case 5:
                deleteEnd();
                cout << "Last element is successfully deleted!" << endl;
                break;
            case 6: {
                int position;
                cout << "Enter position at which you want to delete: ";
                cin >> position;
                deleteAtPosition(position);
                cout << "Deleted successfully!" << endl;
                break;
            }
            case 7:
                display();
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);

    return 0;
}
