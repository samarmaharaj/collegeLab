#include <bits/stdc++.h>
using namespace std;

class Students {
public:
    string name;
    int roll;
    float CGPI;
    int semesters;
    string branch;

    void getDetails() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll: ";
        cin >> roll;
        cout << "Enter CGPI: ";
        cin >> CGPI;
        cout << "Enter semesters: ";
        cin >> semesters;
        cout << "Enter branch: ";
        cin >> branch;
    }

    void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Roll: " << roll << endl;
        cout << "CGPI: " << CGPI << endl;
        cout << "Semesters: " << semesters << endl;
        cout << "Branch: " << branch << endl;
    }

    void CGPIFilter(float k) {
        
        if (CGPI > k) {
            cout << "Name: " << name << endl;
            cout << "Roll: " << roll << endl;
            cout << "CGPI: " << CGPI << endl;
            cout << "Semesters: " << semesters << endl;
            cout << "Branch: " << branch << endl;
        }
    }

    void insertRecord() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll: ";
        cin >> roll;
        cout << "Enter CGPI: ";
        cin >> CGPI;
        cout << "Enter semesters: ";
        cin >> semesters;
        cout << "Enter branch: ";
        cin >> branch;

        cout << "Record inserted successfully!" << endl;
    }
};

int main() {
    cout << "Welcome to Student Management System" << endl;
    int choice = 1;
    int n = 0;
    Students* student = nullptr;

    while (true) {
        cout << "\nChoose from the following options: " << endl;
        cout << "1. Get details of student\n2. Display record of all students\n3. Insert record\n4. CGPI Filter record\n5. Enter to exit.\n" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter number of students: ";
            cin >> n;
            delete[] student; // Clean up previously allocated memory
            student = new Students[n];
            for (int i = 0; i < n; i++) {
                cout << "\n\nEnter details of student " << i + 1 << endl;
                student[i].getDetails();
            }
        } else if (choice == 2) {
            for (int i = 0; i < n; i++) {
                cout << "\n\nDetails of student " << i + 1 << endl;
                student[i].displayDetails();
            }
        } else if (choice == 3) {
            int k;
            cout << "Enter the position at which you want to add a record: ";
            cin >> k;
            if (k < 1 || k > n + 1) {
                cout << "Invalid position!" << endl;
                continue;
            }
            Students* new_student = new Students[n + 1];
            for (int i = 0, j = 0; i < n + 1; i++) {
                if (i == k - 1) {
                    cout << "Enter details for the new student: " << endl;
                    new_student[i].getDetails();
                } else {
                    new_student[i] = student[j++];
                }
            }
            delete[] student;
            student = new_student;
            n++;
        } else if (choice == 4) {
            float k;
            cout << "Enter CGPI filter: ";
            cin >> k;

            for (int i = 0; i < n; i++) {
                student[i].CGPIFilter(k);
            }
        } else {
            break;
        }
    }

    delete[] student; // Clean up allocated memory
    return 0;
}