#include <iostream>
#include <vector>

// Extended Euclidean Algorithm to find GCD and coefficients x and y
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

// Function to solve and print the Linear Diophantine Equation solutions
void solveLDE(char label, int a, int b, int c) {
    int x0, y0;
    int gcd = extendedGCD(abs(a), abs(b), x0, y0);

    // Adjust signs of x0 and y0 based on original signs of a and b
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;

    std::cout << label << ". Equation: " << a << "x + " << b << "y = " << c << std::endl;
    std::cout << "   GCD(" << a << ", " << b << ") = " << gcd << std::endl;

    // A solution exists if and only if GCD(a, b) divides c
    if (c % gcd != 0) {
        std::cout << "   Result: No integer solutions exist because " << gcd << " does not divide " << c << ".\n" << std::endl;
        return;
    }

    // Calculate the particular solution
    int factor = c / gcd;
    int particular_x = x0 * factor;
    int particular_y = y0 * factor;

    // Calculate components for the general solution step sizes
    int step_x = b / gcd;
    int step_y = a / gcd;

    std::cout << "   Result: Solutions exist!" << std::endl;
    std::cout << "   👉 Particular Solution: x0 = " << particular_x << ", y0 = " << particular_y << std::endl;
    std::cout << "   👉 General Solution formula (where k is any integer):" << std::endl;
    std::cout << "      x = " << particular_x << " + (" << step_x << ")k" << std::endl;
    std::cout << "      y = " << particular_y << " - (" << step_y << ")k\n" << std::endl;
}

struct Equation {
    char label;
    int a, b, c;
};

int main() {
    // List of equations from the image
    std::vector<Equation> equations = {
        {'a', 25, 10, 15},
        {'b', 19, 13, 20},
        {'c', 14, 21, 77},
        {'d', 40, 16, 88}
    };

    std::cout << "=== LINEAR DIOPHANTINE EQUATION SOLVER ===\n" << std::endl;

    for (const auto& eq : equations) {
        solveLDE(eq.label, eq.a, eq.b, eq.c);
    }

    return 0;
}
