#include <bits/stdc++.h>
using namespace std;

int maxSubArraySum(int arr[], int n){
    int sum = 0, start = 0, end = 0;
    int max_so_far = arr[0];

    for (int i = 0; i < n; i++){
        sum += arr[i];
        
        //max_so_far = max(max_so_far, sum);
        if ( max_so_far < sum ){
            max_so_far = sum;
        }

        if(sum < 0){
            sum = 0;
        }
    }

    return max_so_far;
}

int main(){
    int a[] = { -2, -3, 4, -1, -2, 1, 5, -3 };
    int n = sizeof(a) / sizeof(a[0]);
 
    // Function Call
    int max_sum = maxSubArraySum(a, n);
    cout << "Maximum contiguous sum is " << max_sum;
    return 0;
}