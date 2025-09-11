#include <bits/stdc++.h>
using namespace std;

int largest(int arr[], int n, int i){
    if (i == n-1){
        return arr[i];
    }

    int max1 = largest(arr, n, i + 1);

    return max(max1, arr[i]);
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Enter the sum of elements :" << max(1, 2);

    return 0;
}