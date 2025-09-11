#include <iostream>
using namespace std;

int binarySearch(int arr[], int size, int item) {
    int high = size - 1, low = 0, mid;

    while(low <= high) {
        mid = (low + high)/2;

        if (arr[mid] == item) {
            return mid;
        } else if (arr[mid] > item) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    int size, item;

    cout << "Enter the size of the array: ";
    cin >> size;

    int* arr = new int[size];

    cout << "Enter the elements of the array in sorted order: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    while(true) {
        cout << "Enter the item to search/delete or insert (0 to exit): ";
        cin >> item;

        if(item == 0) {
            break;
        }

        int index = binarySearch(arr, size, item);

        if (index == -1) {
            cout << "Item not found in the array." << endl;
            cout << "Inserting it into the appropriate position." << endl;
            int i;
            for (i = size - 1; i >= 0 && arr[i] > item; i--) {
                arr[i + 1] = arr[i];
            }
            arr[i + 1] = item;
            size++;
        } else {
            cout << "Item found at index " << index << ". Deleting it from the array." << endl;
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }

        cout << "Array after operation: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    delete[] arr;
    cout << "Thank you for using the program." << endl;
    return 0;
}