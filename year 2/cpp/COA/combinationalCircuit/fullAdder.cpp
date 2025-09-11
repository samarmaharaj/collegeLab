#include <bits/stdc++.h>
#include "../gates.h"
using namespace std;

int carry(vector<int> input) {
    return orfunction({andfunction({input[0], input[1]}), andfunction({input[2], orfunction({input[0], input[1]})})});
}

int main() {
    vector<int> halfAdder = {1, 1};
    vector<int> fullAdder = {0, 0, 1};
    cout << endl;

    cout << "FUll Adder" << endl;
    cout << "Sum: " << xorfunction(fullAdder) << endl;
    cout << "Carry: " << orfunction({andfunction({fullAdder[0], fullAdder[1]}), andfunction({fullAdder[2], orfunction({fullAdder[0], fullAdder[1]})})}) << endl;

    cout << "All possible combination of Full Adder" << endl;
    cout << "=================================================" << endl;
    cout << "WE ARE PROVING CONSENSUS THEOREM:" << endl;
    cout << "=================================================" << endl;
    cout << "+---+---+---+--------+-----+" << endl;
    cout << "| A | B | C | CARRY  | SUM |" << endl;
    cout << "+---+---+---+--------+-----+" << endl;
    for (int i = 0; i < 8; i++) {
        int c = i % 2;
        int b = (i / 2) % 2;
        int a = (i / 4) % 2;

        cout << "| " << a << " | " << b << " | " << c << " | " << carry({a,b,c}) << "      | " << xorfunction({a, b, c}) << "   |" << endl;
    }
    cout << "+---+---+---+--------+-----+" << endl;
    return 0;
}