#include <bits/stdc++.h>
using namespace std;

class students {
        string name;
        int roll;
        float cgpi;
    
public:

    void viewDetails() {
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
        cout << "CGPI: " << cgpi << endl;
    }

    void insertDetails() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll: ";
        cin >> roll;
        cout << "Enter CGPI: ";
        cin >> cgpi;
    }

    void cgpiFilter(float k) {
        if (cgpi > k) {
            viewDetails();
        }
    }

};

int main() {
    int choice = 1;
    int n = 0;
    students* student = nullptr;

    while (true) {
        cout << "\nChoose from the following options: " << endl;
        cout << "1. Get details of student\n2. Display record of all students\n3. Insert record\n4. CGPI Filter record\n5. Enter to exit.\n" << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the number of students: ";
            cin >> n;
            student = new students[n];
            for (int i = 0; i < n; i++) {
                student[i].insertDetails();
            }
        } else if (choice == 2) {
            for (int i = 0; i < n; i++) {
                student[i].viewDetails();
            }
        } else if (choice == 3) {
            cout << "Enter position: ";
            int pos;
            cin >> pos;
            if (pos >= 0 && pos < n) {
                students* temp = new students[n + 1];
                for (int i = 0, j = 0; i < n + 1; i++, j++) {
                    if (i == pos) {
                        temp[i].insertDetails();
                        i++;
                    }
                    temp[i] = student[j];
                }
                delete[] student;
                student = temp;
                n++;
            } else {
                cout << "Invalid position!" << endl;
            }
        } else if (choice == 4) {
            float k;
            cout << "Enter CGPI filter: ";
            cin >> k;
            for (int i = 0; i < n; i++) {
                student[i].cgpiFilter(k);
            }
        } else {
            break;
        }
    }

    delete[] student;
    return 0;
        
}