#include <bits/stdc++.h>

using namespace std;

class ResourceAllocationGraph {
    private:
        int numProcesses;
        int resourceType;
        unordered_map<int, unordered_set<int>> adjList;
        vector<int> available;
    
    public:
        ResourceAllocationGraph(int p, int r) : numProcesses(p), resourceType(r) {
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
            vector<bool> visited(numProcesses + resourceType, false);
            vector<bool> recStack(numProcesses + resourceType, false);
    
            for (int i = 0; i < numProcesses + resourceType; ++i) {
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

int main(){
    cout << "This program simulate RAG ( Resource Allocation Graph ) :\n";
    int numProcesses = 2;
    int resourceType = 2;

    ResourceAllocationGraph rag(numProcesses, resourceType);

 
    // rag.addEdge(5, 0);
    // rag.addEdge(6, 1);
    // rag.addEdge(7, 2);
    // rag.addEdge(8, 0); 
    // rag.addEdge(9, 1); 

    // rag.addEdge(0, 6); 
    // rag.addEdge(1, 7); 
    // rag.addEdge(2, 8);

    // rag.setAvailable(0, 1);
    // rag.setAvailable(1, 0);
    // rag.setAvailable(2, 1);

    rag.addEdge(2, 0);
    rag.addEdge(3, 1);

    rag.addEdge(0, 3);
    rag.addEdge(1, 2);

    rag.setAvailable(0, 0);
    rag.setAvailable(1, 0);


    if (rag.isDeadlocked()) {
        cout << "The system is in a deadlock state." << endl;
    } else {
        cout << "The system is not in a deadlock state." << endl;
    }

    return 0;
}

