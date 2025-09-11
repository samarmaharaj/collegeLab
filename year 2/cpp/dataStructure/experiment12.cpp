#include <iostream>
#include <vector>
using namespace std;

int main() {
     // Number of nodes
    int n = 5;

    // Adjacency matrix (5x5) initialization with 0
    int adjMatrix[5][5] = {0};

    // Adding edges to the adjacency matrix
    adjMatrix[0][2] = 1; // a -> c
    adjMatrix[1][0] = 1; // b -> a
    adjMatrix[1][3] = 1; // b -> d
    adjMatrix[3][2] = 1; // d -> c
    adjMatrix[2][4] = 1; // c -> e

    // Printing adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Transpose of Adjacency Matrix:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjMatrix[j][i] << " ";
        }
        cout << endl;
    }

    cout << endl;
    // Creating adjacency list from adjacency matrix
    vector<int> adjList[5];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1) {
                adjList[i].push_back(j);
            }
        }
    }

    // Printing adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j : adjList[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "Transpose of Adjacency List:" << endl;

    vector<int> adjListTranspose[5];

    for (int i = 0; i < n; i++) {
        for (int j : adjList[i]) {
            adjListTranspose[j].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j : adjListTranspose[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}