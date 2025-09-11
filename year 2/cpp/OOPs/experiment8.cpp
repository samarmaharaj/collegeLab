#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cout << "Base class constructor called" << endl;
    }

    ~Base() {
        cout << "Base class destructor called" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived class constructor called" << endl;
    }

    ~Derived() {
        cout << "Derived class destructor called" << endl;
    }
};

// class Derived2 : public Derived {
// public:
//     Derived2() {
//         cout << "Derived2 class constructor called" << endl;
//     }

//     ~Derived2() {
//         cout << "Derived2 class destructor called" << endl;
//     }

// };

int main() {
    // Derived2 derivedObj;
    Derived derivedObj;
    return 0;
}