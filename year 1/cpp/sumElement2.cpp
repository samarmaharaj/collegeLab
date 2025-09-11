#include <bits/stdc++.h>
using namespace std;

int sum(int arr[], int n){
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int main(){
    int arr[] = {1,2,3,4,5,6,7,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout << "Enter the sum of elements :" << sum(arr, n);

    return 0;
}