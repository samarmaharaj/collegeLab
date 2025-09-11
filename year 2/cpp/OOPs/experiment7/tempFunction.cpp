#include <iostream>
using namespace std;

template <typename T> T findMax(T arr[], int size) {
    T maxElement = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxElement) {
            maxElement = arr[i];
        }
    }
    return maxElement;
}

// int findmax(int arr[]) {
//     int maxElement = arr[0];
//     for (int i = 1; i < 5; i++) {
//         if (arr[i] > maxElement) {
//             maxElement = arr[i];
//         }
//     }
//     return maxElement;
// }

int main() {
    int intArr[] = {1, 5, 3, 9, 2};
    float floatArr[] = {1.5, 2.7, 3.1, 2.4};
    char charArr[] = {'a', 'b', 'c', 'd'};

    int maxInt = findMax(intArr, sizeof(intArr) / sizeof(intArr[0]));
    float maxFloat = findMax(floatArr, sizeof(floatArr) / sizeof(floatArr[0]));
    char maxChar = findMax(charArr, sizeof(charArr) / sizeof(charArr[0]));

    cout << "Maximum integer: " << maxInt << endl;
    cout << "Maximum float: " << maxFloat << endl;
    cout << "Maximum character: " << maxChar << endl;

    return 0;
}

