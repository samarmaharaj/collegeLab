#include <bits/stdc++.h>
#include "../gates.h"
using namespace std;

int deMorganNA(const vector<int>& inputs) {
    int n = inputs.size();
    vector<int> notInputs(n);
    for (int i = 0; i < n; i++) {
        notInputs.push_back(notfunction(inputs[i]));
    }

    return orfunction(notInputs);
}

int deMorganAN(const vector<int>& inputs) {
    int n = inputs.size();
    vector<int> notInputs(n);
    for (int i = 0; i < n; i++) {
        notInputs.push_back(notfunction(inputs[i]));
    }
    return andfunction(notInputs);
}

int main() {
    int a = 1, b = 0;
    cout << "a = " << a << ", b = " << b << endl;

    cout << "(a.b)' = " << deMorganNA({1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1}) << endl;
    cout << "(a + b)' = " << deMorganAN({1, 1, 1, 0}) << endl;

    return 0;
}