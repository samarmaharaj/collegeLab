#include <bits/stdc++.h>
using namespace std;

int main() {

    int row, col;
    cout << "Enter the number of rows: ";
    cin >> row;
    cout << "Enter the number of columns: ";
    cin >> col;

    int matrix1[row][col], matrix2[row][col], sum[row][col];

    cout << "Enter the elements of the first matrix: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter the element at " << i + 1 << " row and " << j + 1 << " column: ";
            cin >> matrix1[i][j];
        }
    }

    cout << "Enter the elements of the second matrix: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "Enter the element at " << i + 1 << " row and " << j + 1 << " column: ";
            cin >> matrix2[i][j];
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    cout << "The sum of the two matrix is: " << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << sum[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}