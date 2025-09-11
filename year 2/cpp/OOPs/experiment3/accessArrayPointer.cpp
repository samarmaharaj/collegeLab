#include <bits/stdc++.h>
using namespace std;

int main() {
    int myArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 9; i++) {
        cout << *(myArray + i) << endl;
    }
    return 0;
}