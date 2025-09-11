#include <bits/stdc++.h>
using namespace std;

class PARENT {
  protected: // Protected access specifier
    int familyIncome;
    int numberOfMembers;
};

class CHILD : public PARENT {
public:
    void setFamilyIncome(int income) {
        familyIncome = income;
    }

    void setNumberOfMembers(int m) {
        numberOfMembers = m;
    }

    void getFamilyIncome() {
        cout << "Family income is: " << familyIncome << endl;
    }

    void getNumberOfMembers() {
        cout << "Total members are: " << numberOfMembers << endl;
    }
};

int main() {
    CHILD samar;
    samar.setFamilyIncome(100000);
    samar.setNumberOfMembers(5);
    samar.getFamilyIncome();
    samar.getNumberOfMembers();

    return 0;
}