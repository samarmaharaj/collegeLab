#include <iostream>
using namespace std;

//Create a class Circle
class Circle {
private:
    float radius;

public:
// Deafult constructor
    Circle() : radius(1.00) {}

//Parametrized constructor
    Circle(float radius) : radius(radius) {}

//Returning Radius
    float getRadius() {
        return radius;
    }

//Operator + overloading
    Circle operator+(const Circle& circle) {
        return Circle(this->radius + circle.radius);
    }
};

int main() {
    Circle C1; // Deafult Calling
    cout << "Radius of 1st Circle: ";
    cout << C1.getRadius() << endl;
    cout << "Radius of 2nd Circle: ";
    Circle C2(10); // Parametrized calling
    cout << C2.getRadius() << endl;

    Circle C3 = C1 + C2; // Operator+ overloading
    cout << "Radius of 3rd Circle (C1 + C2): ";
    cout << C3.getRadius() << endl;

}