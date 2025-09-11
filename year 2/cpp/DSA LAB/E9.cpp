#include <bits/stdc++.h>
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
        } else if (infix[i] = ' ') {
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

int evalPostfix(string postfix) {
    for (int i = 0; i < postfix.length(); i++) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while(isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--;
            push(num);
        } else if (postfix[i] = ' ') {
            continue;
        } else {
            int op2 = pop();
            int op1 = pop();
            int result;
            switch(postfix[i]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
                case '^':
                    result = pow(op1, op2);
                    break;
                default:
                    cout << "Invalid operator" << endl;
                    return -1;
            }
            push(result);
        }
    }

    return pop();
}