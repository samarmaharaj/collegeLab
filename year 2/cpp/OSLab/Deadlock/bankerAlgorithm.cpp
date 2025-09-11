#include <iostream>
#include <vector>

using namespace std;

// Function to check if the system is in a safe state
bool isSafe(vector<vector<int>> &allocation, vector<vector<int>> &max_demand, 
            vector<int> &available, int n, int m, vector<int> &safe_sequence) {
    
    vector<vector<int>> need(n, vector<int>(m)); // Need matrix
    vector<bool> finished(n, false); 
    vector<int> work = available; // Work vector (initially same as available)
    
    // Calculate Need matrix: Need[i][j] = Max[i][j] - Allocation[i][j]
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max_demand[i][j] - allocation[i][j];

    int count = 0; 

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool can_allocate = true;
                
               
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safe_sequence.push_back(i); 
                    finished[i] = true; 
                    found = true;
                    count++;
                }
            }
        }

        if (!found) { 
            return false; 
        }
    }

    return true;
}

int main() {
    int n, m;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    vector<vector<int>> max_demand(n, vector<int>(m));
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter the Maximum Demand matrix:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max_demand[i][j];

    cout << "Enter the Allocation matrix:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "Enter the Available resources:" << endl;
    for (int i = 0; i < m; i++)
        cin >> available[i];

    vector<int> safe_sequence;

    if (isSafe(allocation, max_demand, available, n, m, safe_sequence)) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (int i : safe_sequence)
            cout << "P" << i << " ";
        cout << endl;
    } else {
        cout << "System is in an UNSAFE state." << endl;
    }

    return 0;
}