#include <bits/stdc++.h>
using namespace std;

int division(int d, int q);
int main() {

    int d, q;
    cout << "Enter Dividend: ";
    cin >> d;
    cout << "Enter Divisor: ";
    cin >> q;

    division(d, q);

    return 0;
}

int division(int d, int q) {

    int quotient = d/q;
    int remainder = d%q;

    cout << "The quotient is: " << quotient << endl;
    cout << "The remainder is: " << remainder;

    return 0;
}