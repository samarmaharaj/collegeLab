#include <iostream>
#include <vector>
#include <algorithm> // For min()

using namespace std;

/**
 * @brief Simulates the receiver for Go-Back-N.
 * @param base The first frame the sender is sending in this window.
 * @param end The last frame the sender is sending.
 * @param lost The frame number that will be "lost".
 * @return The sequence number of the last correctly received, in-order frame.
 */
int gbn_receiver(int base, int end, int lost) {
    cout << "  [R] Receiver window expects frame: " << base << "\n";
    int last_good_frame = base - 1;
    for (int i = base; i <= end; ++i) {
        if (i == lost) {
            cout << "  [R] *** Frame " << i << " LOST ***\n";
            // GBN receiver stops accepting frames
            break; 
        }
        cout << "  [R] Received frame " << i << ". Sending ACK.\n";
        last_good_frame = i;
    }
    // GBN sends a cumulative ACK for the last good frame
    cout << "  [R] Sending cumulative ACK for: " << last_good_frame << "\n";
    return last_good_frame;
}

/**
 * @brief Main simulation loop for Go-Back-N.
 */
void gbn_simulate(int N, int total_frames, int lost_frame) {
    int base = 1; // The oldest unacknowledged frame
    
    while (base <= total_frames) {
        int window_end = min(base + N - 1, total_frames);
        
        // --- Sender ---
        cout << "\n[S] Sending window from " << base << " to " << window_end << "...\n";
        for (int i = base; i <= window_end; ++i) {
            if (i == lost_frame) {
                cout << "[S] Sending frame " << i << " (it will be lost)\n";
            } else {
                cout << "[S] Sending frame " << i << "\n";
            }
        }
        
        // --- Receiver ---
        int ack_received = gbn_receiver(base, window_end, lost_frame);
        
        // --- Sender (ACK Processing) ---
        cout << "[S] Received cumulative ACK: " << ack_received << "\n";
        
        if (ack_received == window_end) {
            // All frames in window were ACKed
            base = window_end + 1;
        } else {
            // A frame was lost
            cout << "[S] *** TIMEOUT ***\n";
            cout << "[S] GOING BACK TO N. Resending all from " << ack_received + 1 << "\n";
            base = ack_received + 1; // Sender window slides to the lost frame
            lost_frame = -1; // Simulate loss only once
        }
    }
    cout << "\nAll frames sent and acknowledged.\n";
}


/**
 * @brief Simulates the receiver for Selective Repeat.
 * @param base Sender's window base
 * @param end Sender's window end
 * @param lost The lost frame
 * @param rcv_base Receiver's window base (pass by ref)
 * @param rcv_buffer Receiver's buffer (pass by ref)
 * @param N Window size
 * @return A vector of ACKs for frames received.
 */
vector<int> sr_receiver(int base, int end, int lost, int& rcv_base, vector<bool>& rcv_buffer, int N) {
    vector<int> acks_sent;
    cout << "  [R] Receiver window is [" << rcv_base << "..." << rcv_base + N - 1 << "]\n";
    
    for (int i = base; i <= end; ++i) {
        if (i == lost) {
            cout << "  [R] *** Frame " << i << " LOST ***\n";
            continue; // Skip this frame
        }
        
        // Check if frame is within receiver's window
        if (i >= rcv_base && i < rcv_base + N) {
            cout << "  [R] Received frame " << i << ". Sending individual ACK.\n";
            rcv_buffer[i] = true; // Buffer the frame
            acks_sent.push_back(i);
        } else if (i < rcv_base) {
            // Old frame, re-ACK it
             cout << "  [R] Received duplicate frame " << i << ". Re-sending ACK.\n";
             acks_sent.push_back(i);
        }
    }
    
    // Deliver buffered, in-order frames to application
    while (rcv_base < rcv_buffer.size() && rcv_buffer[rcv_base]) {
        cout << "  [R] Delivering frame " << rcv_base << " to application.\n";
        rcv_base++;
    }
    return acks_sent;
}

/**
 * @brief Main simulation loop for Selective Repeat.
 */
void sr_simulate(int N, int total_frames, int lost_frame) {
    int sender_base = 1;
    int rcv_base = 1;
    
    // State for sender and receiver
    vector<bool> sender_acked(total_frames + 1, false);
    vector<bool> rcv_buffer(total_frames + 1, false);
    
    while (sender_base <= total_frames) {
        int window_end = min(sender_base + N - 1, total_frames);
        
        // --- Sender ---
        cout << "\n[S] Sender window is [" << sender_base << "..." << window_end << "]\n";
        for (int i = sender_base; i <= window_end; ++i) {
            if (!sender_acked[i]) {
                cout << "[S] Sending frame " << i;
                if (i == lost_frame) cout << " (it will be lost)";
                cout << "\n";
            }
        }

        // --- Receiver ---
        vector<int> acks = sr_receiver(sender_base, window_end, lost_frame, rcv_base, rcv_buffer, N);

        // --- Sender (ACK Processing) ---
        bool base_timeout = (lost_frame == sender_base);
        
        for (int ack : acks) {
            if (ack >= sender_base && ack <= window_end) {
                cout << "[S] Received individual ACK for: " << ack << "\n";
                sender_acked[ack] = true;
            }
        }

        // --- Sender (Timeout & Window Sliding) ---
        if (base_timeout) {
            cout << "[S] *** TIMEOUT for frame " << sender_base << " ***\n";
            cout << "[S] SELECTIVELY Resending ONLY frame " << sender_base << "\n";
            lost_frame = -1; // Simulate loss only once
            // In the *next* loop iteration, frame 'sender_base' will be resent
        }
        
        // Slide sender window
        while (sender_base <= total_frames && sender_acked[sender_base]) {
            cout << "[S] Frame " << sender_base << " ACKed. Sliding window base.\n";
            sender_base++;
        }
    }
    cout << "\nAll frames sent and acknowledged.\n";
}

int main() {
    int choice, N, total_frames, lost_frame;
    
    cout << "--- Sliding Window Protocol Simulator ---\n";
    cout << "Select protocol:\n";
    cout << "1. Go-Back-N\n";
    cout << "2. Selective Repeat\n";
    cout << "Choice: ";
    cin >> choice;
    
    cout << "Enter total number of frames to send: ";
    cin >> total_frames;
    cout << "Enter window size (N): ";
    cin >> N;
    cout << "Enter frame to 'lose' (1-" << total_frames << ", or 0 for no loss): ";
    cin >> lost_frame;
    
    if (lost_frame == 0) lost_frame = -1; // Use -1 internally for "no loss"

    if (choice == 1) {
        cout << "\n--- Simulating Go-Back-N ---\n";
        gbn_simulate(N, total_frames, lost_frame);
    } else if (choice == 2) {
        cout << "\n--- Simulating Selective Repeat ---\n";
        sr_simulate(N, total_frames, lost_frame);
    } else {
        cout << "Invalid choice.\n";
    }
    
    return 0;
}
