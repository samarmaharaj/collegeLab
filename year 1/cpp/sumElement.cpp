#include <iostream>
using namespace std;
int main(){
    //int arr[];
    int n;
    int sum = 0;
    cout << "Enter the number of element :";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++){
        cout << "Enter the " << i + 1 << " element : ";
        cin >> arr[i];
    }
    
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    cout << "Enter the sum of elements :" << sum;


}