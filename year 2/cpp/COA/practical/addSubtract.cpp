#include <bits/stdc++.h>
using namespace std;

int add(int a, int b) {
    while (b != 0) {
        int carry = a & b; 
        a = a ^ b;         
        b = carry << 1;    
    }
    return a;
}

int subtract(int a, int b) {
    while (b != 0) {
        int borrow = (~a) & b; 
        a = a ^ b;             
        b = borrow << 1;      
    }
    return a;
}

int main() {
    int choice;
    do {
        cout << "Menu:\n";
        cout << "1. Add two 2-bit binary numbers\n";
        cout << "2. Subtract two 2-bit binary numbers\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string bin1, bin2;
            cout << "Enter first 2-bit binary number (e.g., 00, 01, 10, 11): ";
            cin >> bin1;
            cout << "Enter second 2-bit binary number (e.g., 00, 01, 10, 11): ";
            cin >> bin2;

            if (bin1.length() != 2 || bin2.length() != 2 || 
                bin1.find_first_not_of("01") != string::npos || 
                bin2.find_first_not_of("01") != string::npos) {
                cout << "Invalid input! Please enter 2-bit binary numbers only.\n";
                continue;
            }

            int num1 = stoi(bin1, nullptr, 2); 
            int num2 = stoi(bin2, nullptr, 2); 
            if (choice == 1) {
                int result = add(num1, num2);
                cout << "Result of addition: " << bitset<2>(result) << endl;
            } else {
                int result = subtract(num1, num2);
                cout << "Result of subtraction: " << bitset<2>(result) << endl;
            }
        } else if (choice != 3) {
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    cout << "Exiting program. Goodbye!\n";

    return 0;
}