#include <iostream>
#include <string>


using namespace std;

bool orfunction(const string& inputs) {
    for (char input : inputs) {
        if (input == '1') {
            return true;
        }
    }
    return false;
}

bool andfunction(const string& inputs) {
    for (char input : inputs) {
        if (input == '0') {
            return false;
        }
    }
    return true;
}

bool nandfunction(const string& inputs) {
    for (char input : inputs) {
        if (input == '0') {
            return true;
        }
    }
    return false;
}

bool norfunction(const string& inputs) {
    for (char input : inputs) {
        if (input == '1') {
            return false;
        }
    }
    return true;
}

bool notfunction(char a) {
    return a == '0';
}

bool xorfunction(const string& inputs) {
    int count = 0;
    for (char input : inputs) {
        if (input == '1') {
            count++;
        }
    }
    return count % 2 == 1;
}

bool xnorfunction(const string& inputs) {
    int count = 0;
    for (char input : inputs) {
        if (input == '1') {
            count++;
        }
    }
    return count % 2 == 0;
}

int main() {
    string binaryString = "00";

    for (char input : binaryString) {
        cout << input << " ";
    }

    cout << endl;

    cout << "Or function: " << orfunction(binaryString) << endl;
    cout << "And function: " << andfunction(binaryString) << endl;
    cout << "Not function: " << notfunction('1') << endl;
    cout << "Nand function: " << nandfunction(binaryString) << endl;
    cout << "Nor function: " << norfunction(binaryString) << endl;
    cout << "Xor function: " << xorfunction(binaryString) << endl;
    cout << "Xnor function: " << xnorfunction(binaryString) << endl;

    return 0;
}
