#include <iostream>
using namespace std;

class P {
public:
    int publ = 10;
private:
    int priva = 100;
protected:
    int prote = 1000;
};

// Derived Classes
class A : public P {
public:
    void showInheritance() {
        cout << "Class A (Public Inheritance):\n";
        cout << "publ: Accessible (public)\n" << publ << endl;
        cout << "prote: Accessible (protected)\n" << prote << endl;
        cout << "priva: Not Accessible (private)\n\n"; // priva is not accessible, so we don't try to print it
    }
};

class B : protected P {
public:
    void showInheritance() {
        cout << "Class B (Protected Inheritance):\n";
        cout << "publ: Accessible (protected)\n" << publ << endl;  // publ becomes protected in B
        cout << "prote: Accessible (protected)\n" << prote << endl;
        cout << "priva: Not Accessible (private)\n\n"; // priva is not accessible
    }
};

class C : private P {
public:
    void showInheritance() {
        cout << "Class C (Private Inheritance):\n";
        cout << "publ: Accessible (private)\n" << publ << endl;   // publ becomes private in C
        cout << "prote: Accessible (private)\n" << prote << endl; // prote becomes private in C
        cout << "priva: Not Accessible (private)\n\n"; // priva is not accessible
    }
};

int main() {
    A aObj;
    B bObj;
    C cObj;

    // Setting public variables
    // aObj.publ = 10;  // Allowed since publ is public in A
    // bObj.publ = 20;  // Not allowed, publ is protected in B
    // cObj.publ = 30;  // Not allowed, publ is private in C

    aObj.showInheritance();
    bObj.showInheritance();
    cObj.showInheritance();

    return 0;
}