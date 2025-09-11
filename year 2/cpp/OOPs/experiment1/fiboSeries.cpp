#include <bits/stdc++.h>
using namespace std;

int fibo(int n);
int main() {

    int num;
    cout << "Enter the number of term: ";

    cin >> num;

    for (int i = 1; i <= num; i++) {
        cout << fibo(i) << " ";
    }

    return 0;
}

int fibo(int n) {

    if (n <= 2) {
        return n-1;
    } else {
        return fibo(n - 1) + fibo(n - 2);

    }
}