#include <bits/stdc++.h>
using namespace std;

int linearSearch(int arr[], int val);
int binarySearch(int arr[], int val);
int main() {
    int myArray[8] = {1, 2, 3, 5, 18, 24, 30, 90};
    int val;
    cout << "Enter value to search: ";
    cin >> val;


    linearSearch(myArray, val);
    binarySearch(myArray, val);

    return 0;
}

int linearSearch(int arr[], int val) {

    int index = -1;

    for (int i = 0; i < 8; i++) {
        if (arr[i] == val) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        cout << "\nValue is found at " << index + 1 << " position.";
    } else {
        cout << "\nValue is not found!";
    }

    return 0;
}

int binarySearch(int arr[], int val) {
    int low = 0;
    int high = 8 - 1;
    while ( low <= high ) {
        int mid = (low + high)/2;

        if (val > arr[mid]) {
            low = mid + 1;
        } else if ( val < arr[mid]) {
            high = mid - 1;
        } else {
            cout << "\nValue is found at " << mid + 1 << " position.";
            return 0;
        }
    }

    cout << "\nValue is not found!";

    return 0;
}