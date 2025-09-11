#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Encode 4-bit data into 7-bit Hamming(7,4)
vector<int> encodeNibble(vector<int> data) {
    vector<int> code(7);
    // positions: [p1, p2, d1, p3, d2, d3, d4]
    code[2] = data[0];
    code[4] = data[1];
    code[5] = data[2];
    code[6] = data[3];

    code[0] = code[2] ^ code[4] ^ code[6];       // p1
    code[1] = code[2] ^ code[5] ^ code[6];       // p2
    code[3] = code[4] ^ code[5] ^ code[6];       // p3

    return code;
}

// Decode & correct a 7-bit Hamming(7,4) codeword
vector<int> decodeNibble(vector<int> code) {
    int s1 = code[0] ^ code[2] ^ code[4] ^ code[6];
    int s2 = code[1] ^ code[2] ^ code[5] ^ code[6];
    int s3 = code[3] ^ code[4] ^ code[5] ^ code[6];
    int errorPos = s1 + (s2 << 1) + (s3 << 2);

    if (errorPos != 0 && errorPos <= 7) {
        cout << "  -> Error detected at bit " << errorPos << " in 7-bit block, correcting...\n";
        code[errorPos - 1] ^= 1;
    }

    vector<int> data(4);
    data[0] = code[2];
    data[1] = code[4];
    data[2] = code[5];
    data[3] = code[6];
    return data;
}

// Convert byte to 8-bit binary
vector<int> byteToBits(unsigned char c) {
    vector<int> bits(8);
    for (int i = 7; i >= 0; i--) bits[7-i] = (c >> i) & 1;
    return bits;
}

// Convert 8-bit binary to byte
unsigned char bitsToByte(vector<int> bits) {
    unsigned char c = 0;
    for (int i = 0; i < 8; i++) {
        c = (c << 1) | bits[i];
    }
    return c;
}

int main() {
    while (true) {
        cout << "\n--- Hamming Code Text Transmission ---\n";
        cout << "Enter a text message (or 'exit' to quit): ";
        string msg;
        getline(cin, msg);

        if (msg == "exit") break;
        if (msg.empty()) continue;

        // Show ASCII values
        cout << "\n[Sender] Original message: " << msg << "\n";
        cout << "Hex values: ";
        for (unsigned char c : msg) {
            cout << hex << setw(2) << setfill('0') << (int)c << " ";
        }
        cout << dec << "\n";

        // Encode message
        vector<vector<int>> transmitted; // store codewords
        cout << "Binary values: \n";
        for (int idx = 0; idx < msg.size(); idx++) {
            unsigned char c = msg[idx];
            vector<int> bits = byteToBits(c);

            cout << "  Char '" << msg[idx] << "' -> ";
            for (int b : bits) cout << b;
            cout << "\n";

            // Split into two nibbles and encode
            vector<int> nibble1(bits.begin(), bits.begin()+4);
            vector<int> nibble2(bits.begin()+4, bits.end());

            transmitted.push_back(encodeNibble(nibble1));
            transmitted.push_back(encodeNibble(nibble2));
        }

        // Show encoded stream
        cout << "\n[Sender] Encoded stream: ";
        for (auto& block : transmitted) {
            for (int b : block) cout << b;
            cout << " ";
        }
        cout << "\n";

        // Ask error injection
        cout << "\nDo you want to inject an error? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            int bytePos, bitPos;
            cout << "Enter byte number (1-" << msg.size() << "): ";
            cin >> bytePos;
            cout << "Enter bit position within that byte (1-8): ";
            cin >> bitPos;

            // Map byte/bit to encoded blocks
            int blockIndex = (bytePos-1)*2 + (bitPos <= 4 ? 0 : 1);
            int bitIndex = (bitPos <= 4) ? bitPos-1 : bitPos-5;

            // Find position in 7-bit codeword
            // d1=pos3,d2=pos5,d3=pos6,d4=pos7
            int map[4] = {2,4,5,6};
            int flipPos = map[bitIndex];

            transmitted[blockIndex][flipPos] ^= 1;
            cout << "Injected error in byte " << bytePos << " bit " << bitPos << "\n";
        }
        cin.ignore(); // clear newline

        // Receiver side
        cout << "\n[Receiver] Decoding...\n";
        string recovered;
        for (int i = 0; i < transmitted.size(); i += 2) {
            vector<int> d1 = decodeNibble(transmitted[i]);
            vector<int> d2 = decodeNibble(transmitted[i+1]);

            // Merge into byte
            vector<int> byteBits;
            byteBits.insert(byteBits.end(), d1.begin(), d1.end());
            byteBits.insert(byteBits.end(), d2.begin(), d2.end());

            unsigned char c = bitsToByte(byteBits);
            recovered.push_back(c);
        }

        // Show recovered
        cout << "\n[Receiver] Recovered message: " << recovered << "\n";
        cout << "Hex values: ";
        for (unsigned char c : recovered) {
            cout << hex << setw(2) << setfill('0') << (int)c << " ";
        }
        cout << dec << "\n";
    }

    cout << "Exiting program.\n";
    return 0;
}
