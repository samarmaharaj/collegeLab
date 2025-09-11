#include <bits/stdc++.h>
#include "../gates.h"
using namespace std;

int toBinary(int num) {
    if (num == 0) {
        return 0;
    }

    return (num % 2) + 10 * toBinary(num / 2);
}

string to1sComplement(string binary) {
    for (int i = 0; i < 5; i++){
            binary[i] = binary[i] == '0' ? '1' : '0';
    }

    return binary;
}

string to2sComplement(string binary2) {
    string binary = to1sComplement(binary2);
    int decimal = stoi(binary, nullptr, 2);
    decimal++;
    return bitset<5>(decimal).to_string();
}

int signedForm(string binary) {

    int decimal = stoi(binary.substr(1, 4), nullptr, 2)*-1;
    if (binary[0] == '0') {
        return -decimal;
    }

    return decimal;
}

string toBinaryString(const string& num) {
    int decimal = stoi(num);
    return bitset<5>(decimal).to_string();
}

int main() {

    cout << "Decimal\t\tBinary\tSignedForm\t1s Complement\t2s Complement" << endl;
    int bit = 3;
    int range = pow(2, bit);
    for (int i = 0; i < range; i++) {
        string binary = bitset<5>(i).to_string();
        cout << i << "\t\t" << binary << "\t" << signedForm(binary) << "\t\t" << to1sComplement(binary) << "\t\t" << to2sComplement(binary) << endl;
    }

    return 0;
}