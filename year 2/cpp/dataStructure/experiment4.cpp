#include <iostream>
using namespace std;

// Function to perform binary search
int binarySearch(int arr[], int size, int item) {
    int low = 0, high = size - 1;
    int mid;

    while (low <= high) {
        mid = (low + high) / 2;

        if (arr[mid] == item) {
            return mid; // Item found at index mid
        } else if (arr[mid] < item) {
            low = mid + 1; // Item is in the right half
        } else {
            high = mid - 1; // Item is in the left half
        }
    }

    return -1; // Item not found
}
// Function to delete an item from the array
void deleteItem(int arr[], int& size, int index) {
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
}

// Function to insert an item in the array
void insertItem(int arr[], int& size, int item, int index) {
    for (int i = size - 1; i >= index; i--) {
        arr[i + 1] = arr[i];
    }
    arr[index] = item;
    size++;
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

    while(true) {
        cout << "Array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;

        cout << "Enter the item to search, delete, or insert (0 to exit): ";
        cin >> item;

        if (item == 0) {
            break;
        }

        int index = binarySearch(arr, size, item);


        if (index != -1) {
            cout << "Item found at index " << index << ". Deleting it from the array." << endl;
            deleteItem(arr, size, index);
        } else if (index == -1) {
            cout << "Item not found. Inserting it in the appropriate position to maintain sorted order." << endl;
            // Find the index where the item should be inserted
            int insertIndex = 0;
            while (insertIndex < size && arr[insertIndex] < item) {
                insertIndex++;
            }
            insertItem(arr, size, item, insertIndex);
        } else {
            break;
        }

        cout << "Updated array: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    
    cout << "Thank you for using the program!" << endl;

    delete[] arr;

    return 0;
}