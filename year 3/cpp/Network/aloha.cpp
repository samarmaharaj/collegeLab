#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

using namespace std;

// Simulates one node's attempt
bool transmit(int nodeID, int targetSlot, bool slotted) {
    int attemptSlot = targetSlot;
    if (!slotted) {
        // Pure ALOHA: transmit any time
        cout << "[Node " << nodeID << "] (Pure) Attempting to send.\n";
    } else {
        // Slotted ALOHA: wait for the beginning of the slot
        cout << "[Node " << nodeID << "] (Slotted) Waiting for slot " << targetSlot << " to send.\n";
    }
    return true; // Return true to indicate an attempt
}

void simulate_aloha(bool slotted) {
    srand(time(0));
    int numNodes = 3;
    int targetSlot = 1; // All nodes aim for the same "time"
    
    cout << "\n--- Simulating " << (slotted ? "Slotted" : "Pure") << " ALOHA ---\n";

    vector<int> transmittingNodes;
    for (int i = 1; i <= numNodes; ++i) {
        // Simulate nodes deciding to transmit (50% chance)
        if (rand() % 2 == 0) {
            if (transmit(i, targetSlot, slotted)) {
                transmittingNodes.push_back(i);
            }
        }
    }

    // Check for collision
    if (transmittingNodes.size() == 0) {
        cout << "Channel idle.\n";
    } else if (transmittingNodes.size() == 1) {
        cout << "SUCCESS: Node " << transmittingNodes[0] << " transmitted successfully.\n";
    } else {
        cout << "COLLISION: Nodes ";
        for (int id : transmittingNodes) {
            cout << id << " ";
        }
        cout << "collided. All must retransmit.\n";
    }
}

int main() {
    simulate_aloha(false); // Pure ALOHA
    simulate_aloha(true);  // Slotted ALOHA
    return 0;
}
