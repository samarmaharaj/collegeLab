#include <iostream>
using namespace std;

void showArray(int arr[], int size);

void bubbleSort(int arr[], int size) {
    bool flag;
    for (int i = 0; i < size - 1; i++) {
        flag = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                flag = true;
            }
        }

        if (!flag) {
            break;
        }
    }
}

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

        while(j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

void merge(int arr[], int left[], int right[], int leftSize, int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < leftSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while(j < rightSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int size) {
    if (size <= 1) {
        return;
    }

    int mid = size / 2;

    int left[mid];
    int right[size-mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i - mid] = arr[i];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, right, mid, size - mid);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int i = partition(arr, low, high);

    quickSort(arr, low, i - 1);
    quickSort(arr, i + 1, high);
}


int main() {
    int a1[] = {12, 9, 8, 2, 100, 89, 70, 6, 12, 3};
    int size = sizeof(a1) / sizeof(a1[0]);
    cout << "Unsorted array: ";
    showArray(a1, size);
    bubbleSort(a1, size);
    cout << "Bubble Sorted array: ";
    showArray(a1, size);
    
    int a2[] = {12, 9, 8, 2, 100, 89, 70, 6, 12, 3};
    size = sizeof(a2) / sizeof(a2[0]);
    cout << "Unsorted array: ";
    showArray(a2, size);
    selectionSort(a2, size);
    cout << "Selection Sorted array: ";
    showArray(a2, size);
    
    int a3[] = {12, 9, 8, 2, 100, 89, 70, 6, 12, 3};
    size = sizeof(a3) / sizeof(a3[0]);
    cout << "Unsorted array: ";
    showArray(a3, size);
    selectionSort(a3, size);
    cout << "Insertion Sorted array: ";
    showArray(a3, size);

    int a4[] = {12, 9, 8, 2, 100, 89, 70, 6, 12, 3};
    size = sizeof(a4) / sizeof(a4[0]);
    cout << "Unsorted array: ";
    showArray(a4, size);
    mergeSort(a4, size);
    cout << "MergeSort Sorted array: ";
    showArray(a4, size);

    int a5[] = {12, 9, 8, 2, 100, 89, 70, 6, 12, 3};
    size = sizeof(a5) / sizeof(a5[0]);
    cout << "Unsorted array: ";
    showArray(a5, size);
    quickSort(a5, 0, size - 1);
    cout << "QuickSort Sorted array: ";
    showArray(a5, size);
}

void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}