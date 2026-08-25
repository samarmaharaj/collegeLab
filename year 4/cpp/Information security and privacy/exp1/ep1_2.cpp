#include <iostream>

// This function calculates the GCD and updates x and y using references (&)
int extendedGCD(int a, int b, int &x, int &y) {
    // Base Case: when b becomes 0, we reach the end of our division steps
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1; // To hold the values from the previous step
    int gcd = extendedGCD(b, a % b, x1, y1);

    // Update x and y using the formulas from the table
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main() {
    int a = 161;
    int b = 28;
    int x = 0, y = 0; // These will hold our final answers

    int gcd = extendedGCD(a, b, x, y);

    // Printing the final values
    std::cout << "--- FINAL VALUES ---" << std::endl;
    std::cout << "GCD: " << gcd << std::endl;
    std::cout << "Final x (or s): " << x << std::endl;
    std::cout << "Final y (or t): " << y << std::endl;
    std::cout << "\nVerification: " << a << "*(" << x << ") + " << b << "*(" << y << ") = " << (a * x + b * y) << std::endl;

    return 0;
}
