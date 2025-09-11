#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void insertFront(int value) {
    Node* newNode = new Node;

    if (newNode == NULL) {
        cout << "Memory Error!";
        return;
    }

    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void display() {
    if (head == NULL) {
        cout << "Underflow. Linked List is empty!";
    }

    Node* ptr = head;
    while (ptr != NULL) {
        cout << ptr->data << "->";
        ptr = ptr->next;
    }
    cout << "NULL";
}

Node* newHead = NULL;

void reverseList() {
    Node* current = head;
    Node* prev = NULL;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    newHead = prev;
}

void reverseListDisplay() {
    if (newHead == NULL) {
        cout << "Underflow. Linked List is empty!";
    }

    Node* ptr = newHead;
    while (ptr != NULL) {
        cout << ptr->data << "->";
        ptr = ptr->next;
    }
    cout << "NULL";
}

int main() {
    int choice;
    cout << "Choose:" << endl;
    cout << "1. Insert:" << endl;
    cout << "2. Display:" << endl;
    cout << "3. Reverse:" << endl;
    cout << "4. Exit:" << endl;

    do {

        cout << endl << "Enter your choice:" << endl;
        cin >> choice;
        switch(choice) {
            case 1:
                {
                    int data;
                    cout << "Enter your data: ";
                    cin >> data;
                    insertFront(data);
                    cout << "Inserted successfully!" << endl;
                    break;
                }
            case 2:
                {
                    cout << "Linked List: " << endl;
                    display();
                    break;
                }
            case 3:
                {
                    cout << "Reversed Linked list: " << endl;
                    reverseList();
                    cout << endl;
                    reverseListDisplay();
                    break;
                }
            case 4:
                    cout << "Exiting..." ;
                    break;
            default:
                cout << "Invalid Choice!";
        }

    } while (choice != 4);

    delete[] head;
    delete[] newHead;
    return 0;

}