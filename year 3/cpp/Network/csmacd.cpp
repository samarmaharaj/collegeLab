#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <unistd.h> // For sleep() (simulation)

using namespace std;

// Global "channel"
bool channel_busy = false;

void simulate_csma_cd(int nodeID, int totalNodes) {
    cout << "[Node " << nodeID << "] wants to send.\n";
    
    // 1. CS (Carrier Sense)
    if (channel_busy) {
        cout << "[Node " << nodeID << "] Sensed channel BUSY. Waiting.\n";
        return; // Waits and tries later (simplified)
    }
    
    cout << "[Node " << nodeID << "] Sensed channel IDLE. Starting transmission.\n";
    channel_busy = true;

    // 2. CD (Collision Detection)
    // Simulate another node transmitting simultaneously
    bool collision = false;
    if (nodeID == 1 && totalNodes > 1) { // Simulate collision for Node 1
        cout << "[Node 2] (Simulated) also transmits! COLLISION!\n";
        collision = true;
    }
    
    // Simulate propagation delay
    sleep(1); 

    if (collision) {
        cout << "[Node " << nodeID << "] Detected COLLISION. Stopping transmission.\n";
        cout << "[Node " << nodeID << "] Sending JAM signal.\n";
        channel_busy = false; // Channel clear after jam
        
        // 3. Backoff
        int backoff = rand() % 4 + 1; // Simplified exponential backoff
        cout << "[Node " << nodeID << "] Backing off for " << backoff << "s.\n";
        // sleep(backoff);
        // cout << "[Node " << nodeID << "] Retrying...\n";
    } else {
        cout << "[Node " << nodeID << "] Transmission successful.\n";
        channel_busy = false; // Release channel
    }
}

int main() {
    srand(time(0));
    cout << "--- Simulating CSMA/CD ---\n";
    // Simulate 2 nodes, where node 1 will experience a collision
    simulate_csma_cd(1, 2); 
    // Simulate a 3rd node transmitting successfully after
    simulate_csma_cd(3, 2); 
    return 0;
}
