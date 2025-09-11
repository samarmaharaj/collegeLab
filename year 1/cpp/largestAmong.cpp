#include <bits/stdc++.h>
using namespace std;

int largest(int arr[], int n){
    int max = arr[0];
    for (int i = 0; i < n; i++){
        if (max < arr[i]){
            max = arr[i];
        }
    }
    return max;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Enter the sum of elements :" << largest(arr, n);

    return 0;
}