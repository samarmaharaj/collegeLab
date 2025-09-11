#include <bits/stdc++.h>
#include "..\gates.h"
using namespace std;

int main() {
    cout << "All possible combination of 3 inputs" << endl;
    cout << "=================================================" << endl;
    cout << "WE ARE PROVING CONSENSUS THEOREM:" << endl;
    cout << "=================================================" << endl;
    cout << "+---+---+---+----------------+-------------+" << endl;
    cout << "| A | B | C | AB + A'C + BC  | AB + A'C    |" << endl;
    cout << "+---+---+---+----------------+-------------+" << endl;
    for (int i = 0; i < 8; i++) {
        int c = i % 2;
        int b = (i / 2) % 2;
        int a = (i / 4) % 2;
        cout << "| " << a << " | " << b << " | " << c << " | " << 
        setw(14) << orfunction({andfunction({a, b}), andfunction({notfunction({a}), c}), andfunction({b, c})}) << " | " <<
        setw(11) << orfunction({andfunction({a, b}), andfunction({notfunction({a}), c})}) << " |" << endl;
    }
    cout << "+---+---+---+----------------+-------------+" << endl;
    
    return 0;
}