#include <bits/stdc++.h>
using namespace std;

int largest(int arr[], int n){
    return *max_element(arr, arr + n);
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Enter the sum of elements :" << largest(arr, n);

    return 0;
}