#include <bits/stdc++.h>
using namespace std;

struct Node {
    char data;
    Node* next;
};

Node* head = NULL;

void push(char data) {
    Node* newNode = new Node();
    if (newNode == NULL) {
        cout << "Memory not allocated" << endl;
        return;
    }
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

char pop() {
    if (head == NULL) {
        cout << "Stack is empty. Underflow." << endl;
        return '\0';
    }
    Node* temp = head;
    char val = temp->data;
    head = head->next;
    delete temp;
    return val;
}

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infixToPostfix(string infix) {
    string postfix = "";
    int i = 0;
    while(infix[i] != '\0') {
        if (isalnum(infix[i])) {
            postfix += infix[i];
        } else if (infix[i] == ' ') {
            i++;
            continue;
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (head != NULL && head->data != '(') {
                postfix += pop();
            }
            if (head != NULL && head->data == '(') {
                pop();
            }
        } else {
            while (head != NULL && precedence(infix[i]) <= precedence(head->data)) {
                postfix += pop();
            }
            push(infix[i]);
        }
        i++;
    }

    while (head != NULL) {
        postfix += pop();
    }

    return postfix;
}

int main() {
    string infix;

    while (true) {
        cout << "Enter an infix expression (or press Enter to exit): ";
        getline(cin, infix);

        if (infix.empty()) {
            break;
        }

        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;
    }

    return 0;
}

// buil-in function used: alnum(), getline(), empty() method