#include <bits/stdc++.h>
using namespace std;

int checkEvenOdd(int num);
int main() {

    int num;
    cout << "Enter a number: ";
    cin >> num;

    checkEvenOdd(num);

    return 0;
}

int checkEvenOdd(int num) {

    if (num & 1) {
        cout << "The number is odd." << endl;
    } else {
        cout << "The number is even." << endl;
    }
}