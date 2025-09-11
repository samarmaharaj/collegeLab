#include <bits/stdc++.h>
using namespace std;

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;

    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    // Merge the sorted halves
    int i = 0; 
    int j = 0;
    int k = 0;

    while (i < mid && j < size - mid) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left subarray
    while (i < mid) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right subarray
    while (j < size - mid) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

int partition(int arr[], int low, int high) {
    if (low < high) {
        // Partition the array
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
}
}

void quickSort(int arr[], int low, int high) {
        if (low >= high) {
            return;
        }

        int i = partition(arr, low, high);

        // Recursively sort the subarrays
        quickSort(arr, low, i - 1);
        quickSort(arr, i + 1, high);
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

    cout << "1. Merge Sort\n2. Quick Sort\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        mergeSort(arr, size);

        cout << "Sorted array using Merge sort: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else if (choice == 2) {
        quickSort(arr, 0, size - 1);

        cout << "Sorted array using Quick sort: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    delete[] arr;

    return 0;
}