# Stop-and-Wait Protocol Simulation

## What was fixed:

### 1. **Missing Receiver Invocation**
- **Problem**: The receiver function was defined but never called when frames were sent
- **Fix**: Added `receiver(frameToSend)` call after successful frame transmission

### 2. **Incorrect ACK Sequence Logic**
- **Problem**: Sender was waiting for ACK with sequence number `(1 - nextSequenceNumber)` instead of the same sequence number as the sent frame
- **Fix**: Changed to wait for ACK with sequence number `nextSequenceNumber`

### 3. **Wrong ACK Generation in Receiver**
- **Problem**: Receiver was sending ACK for the next frame instead of acknowledging the current frame
- **Fix**: Changed ACK sequence number to match the received frame's sequence number

### 4. **Threading Library Issues**
- **Problem**: `std::this_thread::sleep_for` was not working with the compiler
- **Fix**: Replaced with Windows `Sleep()` function for better compatibility

## How the Protocol Works:

1. **Sender** sends frames one by one with alternating sequence numbers (0, 1, 0, 1...)
2. **Network** simulates frame loss (20% chance) and ACK loss (20% chance)
3. **Receiver** accepts frames with expected sequence numbers and sends ACKs
4. **Timeout Mechanism** causes sender to retransmit if no ACK is received within 3 seconds

## Key Features:

- ✅ Alternating sequence numbers (0 and 1)
- ✅ Frame loss simulation
- ✅ ACK loss simulation  
- ✅ Timeout and retransmission
- ✅ Duplicate frame detection and handling
- ✅ Proper ACK sequence number matching

## Usage:
```bash
g++ -o stopNwait stopNwait.cpp
./stopNwait.exe
# Enter message when prompted (e.g., "Hello")
```

## Sample Output:
The simulation shows frame transmission, potential losses, timeouts, retransmissions, and successful acknowledgments for each character in the message.