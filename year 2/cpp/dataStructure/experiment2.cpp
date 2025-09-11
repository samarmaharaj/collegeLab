#include <bits/stdc++.h>
using namespace std;

int averageN(float arr[], float A[], int n);
int averageNN(float arr[], float A[], int n);
int show(float arr[], int n);

int main() {
    int n;
    cout << "Enter the number of elements: \n";
    cin >> n;
    float arr[n];
    cout << "Enter the elements: \n";
    for (int i = 0; i < n; i++) {
        cout << "Enter element " << i+1 << ": ";
        cin >> arr[i];
    }
    
    float A1[n];
    float A2[n];
    
    averageN(arr, A1, n);
    averageNN(arr, A2, n);
    cout << "Using O(n) method: ";
    show(A1, n);
    cout << "\n\nUsing O(n^2) method: ";
    show(A2, n);
    return 0;
}

int averageN(float arr[], float A[], int n) {
    A[0] = arr[0];
    for (int i = 1; i < n; i++) {
        A[i] = (A[i-1]*i + arr[i]) / (i+1);
    }

    return 0;
}

int averageNN(float arr[], float A[], int n) {
    
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < i+1; j++) {
            sum += arr[j];
        }

        A[i] = sum / (i+1);
    }

    return 0;
}

int show(float arr[], int n) {
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}