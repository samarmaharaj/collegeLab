#include <iostream>
using namespace std;

template <typename T>
class Rectangle {
private:
    T length;
    T width;

public:
    Rectangle(T l, T w) : length(l), width(w) {}

    T getLength() const {
        return length;
    }

    T getWidth() const {
        return width;
    }

    T getArea() const {
        return length * width;
    }
};

// class RectangleInt {
// private:
//     int length;
//     int width;

// public:
//     RectangleInt(int l, int w) : length(l), width(w) {}

//     int getLength() const {
//         return length;
//     }

//     int getWidth() const {
//         return width;
//     }

//     int getArea() const {
//         return length * width;
//     }
// };

int main() {
    Rectangle<int> rectangle1(5, 10);
    cout << "Rectangle 1 - Length: " << rectangle1.getLength() << ", Width: " << rectangle1.getWidth() << ", Area: " << rectangle1.getArea() << endl;

    Rectangle<float> rectangle2(3.5, 7.2);
    cout << "Rectangle 2 - Length: " << rectangle2.getLength() << ", Width: " << rectangle2.getWidth() << ", Area: " << rectangle2.getArea() << endl;

    return 0;
}