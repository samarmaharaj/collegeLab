#include <iostream>
#include <vector>
using namespace std;

void addEdge(vector<int> adj[], int source, int destination) {
    adj[source].push_back(destination);
}

void adjacencylist(vector<int> adj[], int V) {
    for (int i = 0; i < V; i++) {
        cout << i << ": ";
        for (int j : adj[i]) {
            cout << j << " ";
        }
    }
}

void createGraph(int V, int edges[5][2], int noOfEdges) {

    vector<int> adj[V];
    for (int i = 0; i < noOfEdges; i++) {
        addEdge(adj, edges[i][0], edges[i][1]);
    }
    adjacencylist(adj, V);
}

int main() {
     // Number of nodes
    int n = 5;

    // Adjacency matrix (5x5) initialization with 0
    int adjMatrix[5][5] = {0};

    // Adding edges to the adjacency matrix
    adjMatrix[0][2] = 1; // a -> c
    adjMatrix[1][0] = 1; // b -> a
    adjMatrix[1][3] = 1; // b -> d
    adjMatrix[2][3] = 1; // c -> d
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

    int v = 5;
    int edges[5][2] = {{0, 2}, {1, 0}, {1, 3}, {2, 3}, {2, 4}};
    int noOfEdges = 5;

    createGraph(v, edges, noOfEdges);
    return 0;
}