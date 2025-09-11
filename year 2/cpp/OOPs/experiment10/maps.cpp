#include <bits/stdc++.h>
using namespace std;

int main() {
    map <string, int> record;

    record["elon"] = 1;
    record["osho"] = 2;
    record["samar"] = 3;

    cout << "Record: " << endl;
    for (auto student : record) {
        cout << student.first << " " << student.second << endl;
    }

    string name;
    cout << "Enter the name to search: ";
    cin >> name;

    for (auto student : record) {
        if (student.first == name) {
            cout << "Found: " << endl;
            cout << student.first << " " << student.second << endl;
        }
    }
}