#include <bits/stdc++.h>
using namespace std;

int ascii(char c);
int main() {
    char c;
    cout << "Enter a Charater: ";
    cin >> c;

    cout << "The ASCII value of " << c << " is: ";
    cout << ascii(c);
    return 0;
}

int ascii(char c) {
    int num = c;

    return num;
}