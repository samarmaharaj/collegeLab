#include <iostream>
using namespace std;

class Rectangle {
private:
    float length;
    float breadth;

public:
    // Default constructor
    Rectangle() : length(1.00), breadth(1.00) {}

    // Parameterized constructor
    Rectangle(float l, float b) : length(l), breadth(b) {}

    // Operator overloading for '+'
    Rectangle operator+(const Rectangle& rect) {
        return Rectangle(this->length + rect.length, this->breadth + rect.breadth);
    }

    // Function to calculate area
    float area() const {
        return length * breadth;
    }

    // Friend functions to overload the 'add' function
    friend int add(int length1, int breadth1, int length2, int breadth2);
    friend float add(float length1, float breadth1, float length2, float breadth2);
};

// Function to calculate sum of areas (integer version)
int add(int length1, int breadth1, int length2, int breadth2) {
    Rectangle rect1(length1, breadth1);
    Rectangle rect2(length2, breadth2);
    return rect1.area() + rect2.area();
}

// Function to calculate sum of areas (float version)
float add(float length1, float breadth1, float length2, float breadth2) {
    Rectangle rect1(length1, breadth1);
    Rectangle rect2(length2, breadth2);
    return rect1.area() + rect2.area();
}

int main() {
    // Creating Rectangle objects
    Rectangle rect1(3.0, 4.0);
    Rectangle rect2(5.0, 6.0);

    // Using overloaded + operator to create a new Rectangle
    Rectangle rect3 = rect1 + rect2;

    // Displaying area of the new rectangle
    cout << "Area of new rectangle (rect3): " << rect3.area() << endl;

    // Using overloaded add functions
    cout << "Sum of areas (integer version): " << add(3, 4, 5, 6) << endl;
    cout << "Sum of areas (float version): " << add(3.0f, 4.0f, 5.0f, 6.0f) << endl;

    return 0;
}