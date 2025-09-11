#include <bits/stdc++.h>
using namespace std;

int average(int arr[], int n);
int max(int arr[], int n);
int main() {
    int n;
    cout << "The number of element in the array: ";
    cin >> n;

    int arr[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter " << i + 1 << " elements: ";
        cin >> arr[i];
    }

    average(arr, n);
    max(arr, n);
    return 0;
}

int average(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    cout << "The average of the array is: " << sum / n;
    return 0;
}

int max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    cout << "\nThe maximum element of the array is: " << max;
    return 0;
}