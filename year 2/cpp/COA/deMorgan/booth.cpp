#include <iostream>
#include <math.h>
using namespace std;

int twoComplement(int num){
    return ~num + 1;
}

int decimalToBinary(int num){
    if(num == 1){
        return 1;
    } else {
        return num % 2 + 10 * decimalToBinary(num / 2);
    }
}

void arithmeticRightShift(int &A, int &Q, int &Q_1) {
    int sign_bit = A & (1 << 3);
    Q_1 = Q & 1;

    Q = (Q >> 1) | ((A & 1) << 3);
    A = (A >> 1) | sign_bit;
}

int main(){
    int m = 4;
    int q = 4;
    int a = 0;
    int q_1 = 0;
    int count = log2(q) + 1;



    

    cout << "A: " << a << endl;
    cout << "Q: " << q << endl;
    cout << "100: " << decimalToBinary(100) << endl;


    return 0;
}