#include <iostream>
#include <vector>
#include <unistd.h> // For sleep()

using namespace std;

int main() {
    int numNodes;
    cout << "--- Simulating Token Ring ---\n";
    cout << "Enter number of nodes in ring: ";
    cin >> numNodes;
    if (numNodes <= 0) numNodes = 4;

    int tokenHolder = 0; // Token starts at node 0
    int sender = 2; // Node 2 wants to send
    int receiver = 0; // to Node 0
    string data = "Hello";
    bool data_sent = false;

    for (int round = 0; round < 2; ++round) { // Simulate 2 full rotations
        cout << "\n--- Ring Rotation " << round + 1 << " ---\n";
        for (int i = 0; i < numNodes; ++i) {
            if (i != tokenHolder) continue;

            cout << "Node " << i << " has the token.\n";
            
            if (!data_sent && i == sender) {
                // Node wants to send
                cout << "Node " << i << " is SENDER. Attaching data '" << data 
                     << "' for Node " << receiver << ".\n";
                cout << "Node " << i << " marks token as BUSY.\n";
                data_sent = true; 
            } else if (data_sent && i == receiver) {
                // Node is receiver
                cout << "Node " << i << " is RECEIVER. Copies data: '" << data << "'.\n";
                cout << "Node " << i << " marks frame as received.\n";
            } else if (data_sent && i == sender) {
                // Frame returns to sender
                cout << "Node " << i << " (SENDER) sees frame returned.\n";
                cout << "Node " << i << " re-generates a FREE token.\n";
            } else {
                cout << "Node " << i << " has nothing to send.\n";
            }

            // Pass the token
            tokenHolder = (i + 1) % numNodes;
            cout << "Token passed to Node " << tokenHolder << ".\n";
            sleep(1);
        }
    }
    return 0;
}
