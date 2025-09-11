#include <bits/stdc++.h>
using namespace std;

// Function to perform selection sort
void selectionSort(int arr[], int size) {
    int minIndex;
    for (int i = 0; i < size - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int arr[], int size) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "1. Selection Sort\n2. Insertion Sort\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        selectionSort(arr, size);

        cout << "Sorted array using Selection sort: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else if (choice == 2) {
        insertionSort(arr, size);

        cout << "Sorted array using Insertion sort: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Invalid choice!" << endl;
        return 0;
    }

    delete[] arr;

    return 0;
}