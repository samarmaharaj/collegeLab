#include <iostream>
#include <unistd.h> // For sleep()

using namespace std;

// Simulate the shared wireless medium
bool channel_busy = false;

// Simulates a node (e.g., a laptop) trying to send to another (e.g., Wi-Fi router)
void simulate_csma_ca(int senderID, int receiverID) {
    cout << "\n--- Simulating CSMA/CA (Node " << senderID << " to " << receiverID << ") ---\" << endl;

    // 1. CS (Carrier Sense)
    cout << "[Node " << senderID << "] Senses channel...\n";
    if (channel_busy) {
        cout << "[Node " << senderID << "] Sensed channel BUSY. Waiting (DIFS).\n";
        // In a real sim, would wait for a random backoff time
        return;
    }
    cout << "[Node " << senderID << "] Sensed channel IDLE.\n";

    // 2. CA (Collision Avoidance) - RTS/CTS Handshake
    // Sender sends Request to Send
    cout << "[Node " << senderID << "] -> [Node " << receiverID << "] : Sending RTS (Request to Send)\n";
    
    // Simulate other nodes hearing the RTS and setting their NAV (Network Allocation Vector)
    cout << "[Other Nodes] Heard RTS. Will wait.\n";

    // Receiver responds
    sleep(1); 
    cout << "[Node " << receiverID << "] -> [Node " << senderID << "] : Sending CTS (Clear to Send)\n";
    
    // Simulate other nodes hearing the CTS and updating their NAV
    cout << "[Other Nodes] Heard CTS. Will wait longer.\n";
    channel_busy = true; // Channel is now reserved

    // 3. Send Data
    sleep(1);
    cout << "[Node " << senderID << "] -> [Node " << receiverID << "] : Sending DATA...\n";

    // 4. Acknowledgment
    sleep(2); // Simulate data transmission time
    cout << "[Node " << receiverID << "] -> [Node " << senderID << "] : Sending ACK (Acknowledgment)\n";
    
    cout << "[Node " << senderID << "] Received ACK. Transmission successful.\n";
    channel_busy = false; // Channel is free
}

int main() {
    // Simulate Node 1 sending to Node 10 (the Access Point)
    simulate_csma_ca(1, 10);
    
    // Simulate Node 2 trying to send, but finding the channel busy
    channel_busy = true; // Manually set for simulation
    cout << "\n--- A different node tries to send ---" << endl;
    simulate_csma_ca(2, 10);
    channel_busy = false;
    
    return 0;
}
