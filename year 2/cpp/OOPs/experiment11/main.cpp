// main.cpp
#include <iostream>
#include "array_utils.h"
using namespace std;

int main() {
    int arr[] = {5, 10, 15, 20, 25, 30};
    int size = sizeof(arr) / sizeof(arr[0]);

    cout << "Array elements: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Using functions from the user-defined header file
    cout << "Average of elements: " << average(arr, size) << endl;
    cout << "Maximum element: " << maximum(arr, size) << endl;
    cout << "Size of array: " << array_size(arr, size) << endl;

    return 0;
}

