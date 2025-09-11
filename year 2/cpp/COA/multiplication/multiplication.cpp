#include <bits/stdc++.h>
using namespace std;

int DecimalToBinary(int num) {
    if (num == 1) {
        return 1;
    } else {
        return num%2 + 10 * DecimalToBinary(num/2);
    }
}

int main() {
    int result = 0;
    int m = 23;
    int q = 20; 

    int iterations = log2(q) + 1;
    for (int i = 0; i < iterations; i++) {
        if ( q & 1 ) {
            result += m << (i);
        }
        q = q/2;
    }

    cout << "Result: " << result << endl;   

    return 0;
}