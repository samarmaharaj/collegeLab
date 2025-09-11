#include <iostream>
using namespace std;

int arr[5] = {0, 0, 0, 0, 0};

int front = -1;
int rear = -1;

void insert() {
    int x;

    if ((front == 0 && rear == 4) || (rear == front - 1)) {
        cout << "Queue is full" << endl;
    } else {
        cout << "Enter the data:" << endl;
        cin >> x;

        if (front == -1) {
            front = rear = 0;
        } else if (rear == 4) {
            rear = 0;
        } else {
            rear++;
        }

        arr[rear] = x;
    }
}

int del() {
    int x;

    if (front == -1) {
        cout << "Queue is empty" << endl;
        return -1;
    } else {
        x = arr[front];

        if (front == rear) {
            front = rear = -1;
        } else if (front == 4) {
            front = 0;
        } else {
            front++;
        }

        return x;
    }
}

void display() {
    if (front == -1) {
        cout << "Queue is empty" << endl;
    } else {
        for (int i = front; i != rear; i = (i + 1) % 5) {
            cout << arr[i] << "--";
        }
        cout << arr[rear] << "--";
    }
}

int main() {
    int choice;

    do{
        cout << endl;
        cout << "Menu: Circular Queue Operation:" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice:" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                cout << "Deleted element is: " << del() << endl;
                break;
            case 3:
                display();
                break;
            case 4:
                cout << "Exit" << endl;
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    } while (choice != 4);

    return 0;
}