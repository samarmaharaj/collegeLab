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

int evalPostfix(string postfix) {
    for (int i = 0; i < postfix.length(); i++) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--; // to adjust for the extra increment in the while loop
            push(num);
        } else if (postfix[i] == ' ') {
            continue;
        } else {
            int op2 = pop();
            int op1 = pop();
            int result;
            switch (postfix[i]) {
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

int main() {
    string postfix = "20 25 * 25 5 / 5 + /";

    int val = evalPostfix(postfix);
    cout << "Result: " << val << endl;
}