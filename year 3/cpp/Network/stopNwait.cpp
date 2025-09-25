#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h> // For Sleep function on Windows

// --- Configuration ---
// Chance (out of 100) for a frame to be lost in transit.
const int FRAME_LOSS_CHANCE = 20;
// Chance (out of 100) for an acknowledgment to be lost.
const int ACK_LOSS_CHANCE = 20;
// Timeout duration in seconds for the sender to wait for an ACK.
const int TIMEOUT_SECONDS = 3;

// A simple structure to represent a data frame.
struct Frame {
    int sequenceNumber; // Sequence number (0 or 1)
    std::string data;   // The data being sent (a single character in this simulation)
    bool isAck;         // Flag to differentiate data frames from ACKs
};

// --- Function Prototypes ---
void sender(const std::string& message);
void receiver(Frame receivedFrame);

// --- Global state variables to simulate the shared channel/medium ---
// Simulates the physical channel. A null frame means the channel is empty.
Frame channel;
bool channelBusy = false;

// --- Main Simulation ---
int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    std::string message;
    std::cout << "Enter the message to send: ";
    std::getline(std::cin, message);

    if (message.empty()) {
        std::cout << "Message is empty. Nothing to send." << std::endl;
        return 0;
    }

    std::cout << "\n--- Starting Stop-and-Wait Protocol Simulation ---" << std::endl;
    
    // The sender starts the process. The receiver logic is implicitly called
    // through the shared 'channel' state.
    sender(message);

    std::cout << "\n--- Simulation Finished ---" << std::endl;
    std::cout << "Message sent and acknowledged successfully." << std::endl;

    return 0;
}

/**
 * @brief Simulates the sender side of the protocol.
 * * @param message The complete message to be sent frame by frame.
 */
void sender(const std::string& message) {
    int nextSequenceNumber = 0;

    for (char const &character : message) {
        Frame frameToSend;
        frameToSend.sequenceNumber = nextSequenceNumber;
        frameToSend.data = character;
        frameToSend.isAck = false;

        while (true) {
            std::cout << "[Sender] Preparing to send frame " << frameToSend.sequenceNumber 
                      << " with data: '" << frameToSend.data << "'" << std::endl;
            
            // Simulate sending the frame over the channel
            channel = frameToSend;
            channelBusy = true;

            // Simulate potential loss of the data frame
            if (rand() % 100 < FRAME_LOSS_CHANCE) {
                std::cout << "[Network] >> FRAME " << frameToSend.sequenceNumber << " was LOST! <<\n" << std::endl;
                channelBusy = false; // Frame is lost
            } else {
                std::cout << "[Network] Frame " << frameToSend.sequenceNumber << " sent to receiver." << std::endl;
                // Call the receiver function to process the frame
                receiver(frameToSend);
            }

            // Start timer and wait for acknowledgment
            std::cout << "[Sender] Waiting for ACK " << nextSequenceNumber << " (Timeout: " << TIMEOUT_SECONDS << "s)" << std::endl;
            Sleep(TIMEOUT_SECONDS * 1000); // Sleep for timeout duration (in milliseconds)

            // Check if an ACK was received in the channel
            if (channelBusy && channel.isAck && channel.sequenceNumber == nextSequenceNumber) {
                std::cout << "[Sender] Received correct ACK " << channel.sequenceNumber << "." << std::endl;
                channelBusy = false; // Sender has processed the ACK
                
                // Flip the sequence number for the next frame
                nextSequenceNumber = 1 - nextSequenceNumber; 
                std::cout << "----------------------------------------------------" << std::endl;
                break; // Exit the while loop to send the next character
            } else {
                // This block handles two cases:
                // 1. Timeout: No ACK was received at all (channelBusy is false).
                // 2. Wrong ACK: An old or duplicate ACK was received.
                std::cout << "\n[Sender] >> TIMEOUT or wrong ACK! << Resending frame " << frameToSend.sequenceNumber << ".\n" << std::endl;
            }
        }
    }
}


/**
 * @brief Simulates the receiver side of the protocol.
 * This function is called implicitly whenever the sender puts data on the channel.
 * * @param frame The frame received from the sender.
 */
void receiver(Frame receivedFrame) {
    static int expectedSequenceNumber = 0;
    
    std::cout << "[Receiver] Received a frame. Expected seq: " << expectedSequenceNumber << ". Got seq: " << receivedFrame.sequenceNumber << "." << std::endl;

    // Check if the received frame has the expected sequence number
    if (receivedFrame.sequenceNumber == expectedSequenceNumber) {
        std::cout << "[Receiver] Frame " << receivedFrame.sequenceNumber << " is correct. Data: '" << receivedFrame.data << "' accepted." << std::endl;

        // Prepare the acknowledgment for the current frame
        Frame ackFrame;
        ackFrame.sequenceNumber = expectedSequenceNumber; // ACK with same sequence number as received frame
        ackFrame.isAck = true;

        // Flip the expected sequence number for the next incoming frame
        expectedSequenceNumber = 1 - expectedSequenceNumber;
        
        // Simulate potential loss of the acknowledgment
        if (rand() % 100 < ACK_LOSS_CHANCE) {
            std::cout << "[Network] >> ACK " << ackFrame.sequenceNumber << " was LOST! <<\n" << std::endl;
            channelBusy = false; // Ack is lost, sender will time out
        } else {
            // Send the ACK back to the sender
            channel = ackFrame;
            channelBusy = true;
            std::cout << "[Network] ACK " << ackFrame.sequenceNumber << " sent to sender." << std::endl;
        }

    } else {
        std::cout << "[Receiver] Duplicate frame " << receivedFrame.sequenceNumber << " detected. Discarding." << std::endl;
        
        // Resend acknowledgment for the last correctly received frame
        Frame ackFrame;
        ackFrame.sequenceNumber = 1 - expectedSequenceNumber; // ACK for the previous frame we accepted
        ackFrame.isAck = true;

        channel = ackFrame; // Resend previous ACK
        channelBusy = true;
        std::cout << "[Network] Re-sending previous ACK " << ackFrame.sequenceNumber << "." << std::endl;
    }
}
