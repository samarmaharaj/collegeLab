#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void push(int data) {
    Node* newNode = new Node();
    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

int pop() {
    if (head == NULL) {
        cout << "Stack is empty. Underflow." << endl;
        return -1;
    }
    Node* temp = head;
    int val = temp->data;
    head = head->next;
    delete temp;
    return val;
}

int peek() {
    if (head == NULL) {
        cout << "Stack is empty. No element is present." << endl;
        return -1;
    }
    return head->data;
}

void display() {
    if (head == NULL) {
        cout << "Stack is empty" << endl;
        return;
    }
    Node* ptr = head;
    while (ptr != NULL) {
        cout << ptr->data << " -> ";
        ptr = ptr->next;
    }
    cout << "NULL" << endl;
}

int main() {
    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Peek" << endl;
        cout << "4. Display" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                int data;
                cout << "Enter data: ";
                cin >> data;
                push(data);
                break;
            }
            case 2: {
                int poppedValue = pop();
                if (poppedValue != -1) {
                    cout << "The element " << poppedValue << " is deleted." << endl;
                }
                break;
            }
            case 3: {
                int topValue = peek();
                if (topValue != -1) {
                    cout << "Top element is: " << topValue << endl;
                }
                break;
            }
            case 4: {
                display();
                break;
            }
            case 5: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
            }
        }
    } while (choice != 5);

    return 0;
}
