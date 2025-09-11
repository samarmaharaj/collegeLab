#include <iostream>
#include <vector>
using namespace std;

int main() {
    // a) Predefined with a set of values
    vector<int> vecA = {1, 0, 3, 4, 5};

    // b) Vector of size 5
    vector<int> vecB(5);

    // c) Vector of size 5 with all values initialized to 0
    vector<int> vecC(5, 0);

    // d) An exact copy of vector C
    vector<int> vecD = vecC;

    cout << "Vector A: ";
    for (int val : vecA) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Vector B: ";
    for (int val : vecB) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Vector C: ";
    for (int val : vecC) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Vector D: ";
    for (int val : vecD) {
        cout << val << " ";
    }
    cout << endl;

    vecC.push_back(5);
    cout << "Vector C after push_back 2: ";
    for (int val : vecC) {
        cout << val << " ";
    }
    cout << endl;

    vecC.pop_back();
    vecC.pop_back();

    cout << "Vector C after pop_back two times: ";
    for (int val : vecC) {
        cout << val << " ";
    }


    return 0;
}