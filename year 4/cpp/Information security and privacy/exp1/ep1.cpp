#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int extendedGCD(int a, int b, int &x, int &y) {
    if(a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int main() {
    int n;
    cout << "Enter number of integers: ";
    cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << " integer: ";
        cin >> arr[i];
    }

    int result = arr[0];
    for(int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
    }

    cout << "GCD of the entered integers is: " << result << endl;

}