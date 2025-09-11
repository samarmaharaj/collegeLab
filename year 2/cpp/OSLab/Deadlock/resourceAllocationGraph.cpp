#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class ResourceAllocationGraph {
private:
    int numProcesses;
    int numResources;
    unordered_map<int, unordered_set<int>> adjList;
    vector<int> available;

public:
    ResourceAllocationGraph(int p, int r) : numProcesses(p), numResources(r) {
        available.resize(r, 0);
    }

    void addEdge(int from, int to) {
        adjList[from].insert(to);
    }

    void removeEdge(int from, int to) {
        adjList[from].erase(to);
    }

    void setAvailable(int resource, int value) {
        available[resource] = value;
    }

    bool isDeadlocked() {
        vector<bool> visited(numProcesses + numResources, false);
        vector<bool> recStack(numProcesses + numResources, false);

        for (int i = 0; i < numProcesses + numResources; ++i) {
            if (isCyclic(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    bool isCyclic(int node, vector<bool>& visited, vector<bool>& recStack) {
        if (!visited[node]) {
            visited[node] = true;
            recStack[node] = true;

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor] && isCyclic(neighbor, visited, recStack)) {
                    return true;
                } else if (recStack[neighbor]) {
                    return true;
                }
            }
        }
        recStack[node] = false;
        return false;
    }
};

int main() {
    int numProcesses = 5;
    int numResources = 3;

    ResourceAllocationGraph rag(numProcesses, numResources);

    // Example allocation matrix
    rag.addEdge(5, 0); // P0 -> R0
    rag.addEdge(6, 1); // P1 -> R1
    rag.addEdge(7, 2); // P2 -> R2
    rag.addEdge(8, 0); // P3 -> R0
    rag.addEdge(9, 1); // P4 -> R1

    // Example request matrix
    rag.addEdge(0, 6); // R0 -> P1
    rag.addEdge(1, 7); // R1 -> P2
    rag.addEdge(2, 8); // R2 -> P3

    // Example available resources
    rag.setAvailable(0, 1);
    rag.setAvailable(1, 0);
    rag.setAvailable(2, 1);

    if (rag.isDeadlocked()) {
        cout << "The system is in a deadlock state." << endl;
    } else {
        cout << "The system is not in a deadlock state." << endl;
    }

    return 0;
}
