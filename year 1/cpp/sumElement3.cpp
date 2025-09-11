#include <bits/stdc++.h>
using namespace std;

int sum(int arr[], int n){
    if (n == 0){
        return 0;
    } else {
        return arr[n-1] + sum(arr, n-1);
    }
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Enter the sum of elements :" << sum(arr, n);

    return 0;
}