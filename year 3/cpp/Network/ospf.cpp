#include <iostream>
#include <vector>
#include <map>
#include <queue> // For priority_queue

using namespace std;

#define INF 999

// Implements Dijkstra's algorithm
void run_dijkstra(int startNode, int numNodes, const vector<vector<int>>& graph) {
    map<int, int> dist;
    for (int i = 0; i < numNodes; ++i) {
        dist[i] = INF;
    }
    dist[startNode] = 0;

    // min-priority queue
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, startNode}); // {distance, node}

    cout << "\n--- Dijkstra's Algorithm from Node " << startNode << " ---\n";
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue; // Skip old entry

        // For each neighbor 'v' of 'u'
        for (int v = 0; v < numNodes; ++v) {
            int weight = graph[u][v];
            if (weight != 0 && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest path table for Router " << startNode << ":\n";
    for (int i = 0; i < numNodes; ++i) {
        cout << "  To " << i << ": cost " << dist[i] << "\n";
    }
}

int main() {
    cout << "--- Simulating OSPF (Link State) ---\n";
    int numNodes = 4;
    // Adjacency matrix (0 = no link)
    vector<vector<int>> graph = {
    //   0  1  2  3
        {0, 1, 5, 0}, // Node 0
        {1, 0, 2, 0}, // Node 1
        {5, 2, 0, 3}, // Node 2
        {0, 0, 3, 0}  // Node 3
    };

    cout << "Network Graph (Adjacency Matrix):\n";
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 1. (Simulated) All nodes flood their links (the graph above)
    cout << "\n(Simulated) All nodes flood LSPs to build this graph.\n";
    
    // 2. Each router runs Dijkstra on the full graph
    // We'll just run it for Node 0
    run_dijkstra(0, numNodes, graph);
    
    return 0;
}
