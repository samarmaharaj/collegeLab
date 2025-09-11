#include <iostream>
#include <cmath>
#include <bitset>

using namespace std;

// Function to get two's complement
int twoComplement(int num, int bits) {
    return (~num + 1) & ((1 << bits) - 1);  // Ensuring two's complement within bit range
}

// Function to perform arithmetic right shift
void arithmeticRightShift(int &A, int &Q, int &Q_1, int bitLength) {
    int sign_bit = A & (1 << (bitLength - 1)); // Preserve sign bit
    Q_1 = Q & 1;  // Save the LSB of Q before shifting

    Q = (Q >> 1) | ((A & 1) << (bitLength - 1)); // Shift Q with A's LSB
    A = (A >> 1) | sign_bit; // Shift A, preserving sign
}

// Booth's Algorithm Implementation
void boothMultiplication(int M, int Q, int bitLength) {
    int A = 0, Q_1 = 0;
    int count = bitLength;

    cout << "Step\tA\t\tQ\t\tQ-1\tOperation" << endl;
    while (count > 0) {
        cout << count << "\t" << bitset<8>(A) << "\t" << bitset<8>(Q) << "\t" << Q_1 << "\t";

        if ((Q & 1) == 1 && Q_1 == 0) {  // 01 Case: Subtract M
            A = A + twoComplement(M, bitLength);
            cout << "A = A - M";
        } else if ((Q & 1) == 0 && Q_1 == 1) {  // 10 Case: Add M
            A = A + M;
            cout << "A = A + M";
        } else {
            cout << "No operation";
        }

        arithmeticRightShift(A, Q, Q_1, bitLength);
        cout << endl;
        count--;
    }

    cout << "Final Result (A & Q): " << bitset<8>(A) << " " << bitset<8>(Q) << endl;
    cout << "Product: " << (A << bitLength | Q) << endl;
}

// Convert decimal to binary (fixed)
string decimalToBinary(int num) {
    return bitset<8>(num).to_string();  // Converts to 8-bit binary string
}

// Main function
int main() {
    int M = 20, Q = 5;  // Multiplicand & Multiplier
    int bitLength = 8;  // 8-bit representation

    boothMultiplication(M, Q, bitLength);

    cout << "Binary of 100: " << decimalToBinary(1000) << endl;

    return 0;
}
