#include <bits/stdc++.h>
using namespace std;

void swap(int* n1, int* n2);
int main() {

    int num1, num2;

    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    swap(&num1, &num2);

    return 0;
}


void swap(int* n1, int* n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;

    cout << "After swapping, firstNumber = " << *n1 << "\n";
    cout << "After swapping, secondNumber = " << *n2;
}