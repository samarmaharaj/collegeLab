#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> orderedSet;
    unordered_set<int> unorderedSet;

    int values[] = {1, 2, 4, 3, 6, 2};

    for (int value : values) {
        orderedSet.insert(value);
        unorderedSet.insert(value);
    }

    cout << "Ordered Set: ";
    for (const int& value : orderedSet) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Unordered Set: ";
    for (const int& value : unorderedSet) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}