#include <bits/stdc++.h>
using namespace std;

int main() {

    class Array {
    public: 
        int year = 2024;
        int height = 2;
    };

    Array* myArray = nullptr;

    myArray = new Array[10];
    for (int i = 0; i < 10; i++) {
        cout << myArray[i].year << endl;
    }

    return 0;
}