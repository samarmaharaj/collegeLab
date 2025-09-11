#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    double num1, num2;
    cout << "Enter numerator: ";
    cin >> num1;
    cout << "Enter denominator: ";
    cin >> num2;

    try {
        if (num2 == 0) {
            if (num1 == 0) {
                throw runtime_error("0/0 -> Not defined");
            } else {
                throw runtime_error("1/0 -> Infinity");
            }
        }
        int result = num1 / num2;
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}