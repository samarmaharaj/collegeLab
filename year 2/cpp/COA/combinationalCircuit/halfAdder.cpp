#include <bits/stdc++.h>
#include "../gates.h"
using namespace std;

int main() {
    vector<int> halfAdder = {1, 1};
    vector<int> fullAdder = {0, 0, 1};
    cout << endl;

    cout << "Half Adder" << endl;
    cout << "Sum: " << xorfunction(halfAdder) << endl;
    cout << "Carry: " << andfunction(halfAdder) << endl;

    cout << "All possible combination of Half Adder" << endl;
    cout << "=================================================" << endl;
    cout << "WE ARE PROVING CONSENSUS THEOREM:" << endl;
    cout << "=================================================" << endl;
    cout << "+---+---+--------+-----+" << endl;
    cout << "| A | B | CARRY  | SUM |" << endl;
    cout << "+---+---+--------+-----+" << endl;
    for (int i = 0; i < 4; i++) {
        int b = i % 2;
        int a = (i / 2) % 2;

        cout << "| " << a << " | " << b << " | " << andfunction({a, b}) << "      | " << xorfunction({a, b}) << "   |" << endl;
    }
    cout << "+---+---+--------+-----+" << endl;
    return 0;
}