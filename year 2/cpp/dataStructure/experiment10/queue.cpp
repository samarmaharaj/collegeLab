#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;
};

Node *front = NULL;
Node *rear = NULL;

void insert() {
    Node *temp = new Node();
    int val;

    cout << "Enter the value to be inserted:" << endl;
    cin >> val;
    temp->data = val;
    temp->next = NULL;

    if (front == NULL) {
        front = rear = temp;
    } else {    
        rear->next = temp;
        rear = temp;
    }
}

int del() {
    Node *ptr = front;
    int x = -1;

    if (front == NULL) {
        cout << "Queue is empty" << endl;
    } else {
        front = front->next;
        x = ptr->data;
        delete ptr;
    }

    return x;
}

void display() {
    Node *ptr = front;

    if (front == NULL) {
        cout << "Queue is empty" << endl;
    } else {
        while (ptr != NULL) {
            cout << ptr->data << "<--";
            ptr = ptr->next;
        }
    }
}


int main() {
    int choice;

    do{
        cout << endl;
        cout << "Menu:" << endl;
        cout << "Enter your choice:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Display" << endl;
        cout << "4. exit" << endl;

        cin >> choice;

        switch(choice) {
            case 1: insert();
                    break; 
                
            case 2:
                    cout << "Deleted element is:" << del() << endl;
                    break;

            case 3: display();
                    break;

            case 4: exit(0);
        }
    } while (choice != 4);

    return 0;
};