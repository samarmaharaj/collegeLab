// Sender/Receiver demo with menu: Parity (even/odd), 16-bit checksum, CRC-16-CCITT
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <limits>

using namespace std;

vector<uint8_t> toBytes(const string& s) { return {s.begin(), s.end()}; }

void printHex(const vector<uint8_t>& data) {
    ios::fmtflags f(cout.flags());
    for (size_t i = 0; i < data.size(); ++i)
        cout << hex << uppercase << setw(2) << setfill('0') << (unsigned)data[i] << (i + 1 != data.size() ? " " : "");
    cout.flags(f);
}

uint8_t parityBit(const vector<uint8_t>& data, bool even) {
    unsigned ones = 0;
    for (uint8_t b : data)
        ones += __builtin_popcount(b);
    return static_cast<uint8_t>(even ? (ones & 1u) : ((ones & 1u) ^ 1u));
}

uint16_t checksum16(const vector<uint8_t>& data) {
    uint32_t sum = 0;
    size_t i = 0;
    for (; i + 1 < data.size(); i += 2) {
        sum += (data[i] << 8) | data[i + 1];
        if (sum > 0xFFFF) sum = (sum & 0xFFFF) + 1;
    }
    if (i < data.size()) {
        sum += (data[i] << 8);
        if (sum > 0xFFFF) sum = (sum & 0xFFFF) + 1;
    }
    return static_cast<uint16_t>(~sum & 0xFFFF);
}

uint16_t crc16_ccitt(const vector<uint8_t>& data, uint16_t poly = 0x1021, uint16_t init = 0xFFFF) {
    uint16_t crc = init;
    for (uint8_t byte : data) {
        crc ^= (byte << 8);
        for (int i = 0; i < 8; ++i)
            crc = (crc & 0x8000) ? (crc << 1) ^ poly : (crc << 1);
    }
    return crc;
}

enum class Method { ParityEven = 1, ParityOdd, Checksum16, CRC16 };

const char* methodName(Method m) {
    switch (m) {
        case Method::ParityEven: return "Even Parity";
        case Method::ParityOdd:  return "Odd Parity";
        case Method::Checksum16: return "16-bit Checksum";
        case Method::CRC16:      return "CRC-16-CCITT";
        default: return "Unknown";
    }
}

void flipBit(vector<uint8_t>& bytes, size_t byteIndex, int bitIndex) {
    if (byteIndex < bytes.size() && bitIndex >= 0 && bitIndex < 8)
        bytes[byteIndex] ^= (1u << bitIndex);
}

vector<uint8_t> buildFrame(const vector<uint8_t>& payload, Method m) {
    vector<uint8_t> frame = payload;
    switch (m) {
        case Method::ParityEven:
        case Method::ParityOdd:
            frame.push_back(parityBit(payload, m == Method::ParityEven));
            break;
        case Method::Checksum16: {
            uint16_t sum = checksum16(payload);
            frame.push_back(sum >> 8);
            frame.push_back(sum & 0xFF);
            break;
        }
        case Method::CRC16: {
            uint16_t crc = crc16_ccitt(payload);
            frame.push_back(crc >> 8);
            frame.push_back(crc & 0xFF);
            break;
        }
    }
    return frame;
}

bool verifyFrame(const vector<uint8_t>& frame, Method m, vector<uint8_t>& outPayload) {
    if (frame.empty()) { outPayload.clear(); return false; }
    switch (m) {
        case Method::ParityEven:
        case Method::ParityOdd: {
            if (frame.size() < 1) return false;
            uint8_t parity = frame.back() & 1u;
            outPayload.assign(frame.begin(), frame.end() - 1);
            return parity == parityBit(outPayload, m == Method::ParityEven);
        }
        case Method::Checksum16:
        case Method::CRC16: {
            if (frame.size() < 2) return false;
            uint16_t recv = (frame[frame.size()-2] << 8) | frame.back();
            outPayload.assign(frame.begin(), frame.end() - 2);
            uint16_t calc = (m == Method::Checksum16) ? checksum16(outPayload) : crc16_ccitt(outPayload);
            return recv == calc;
        }
        default: return false;
    }
}

int main() {
    while (true) {
        cout << "Enter data (text line): ";
        string line;
        getline(cin >> ws, line);
        vector<uint8_t> payload = toBytes(line);

        cout << "\nChoose method:\n"
             << "  1) Even Parity\n"
             << "  2) Odd Parity\n"
             << "  3) 16-bit Checksum (one's complement)\n"
             << "  4) CRC-16-CCITT\n"
             << "  0) Exit\n"
             << "Enter choice: ";
        int choice = 0;
        if (!(cin >> choice) || choice < 0 || choice > 4) {
            cout << "Exiting...\n";
            break;
        }
        if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }
        Method method = static_cast<Method>(choice);

        cout << "\nSender: payload (hex): ";
        printHex(payload);
        cout << "\nSender: method = " << methodName(method) << '\n';

        vector<uint8_t> frame = buildFrame(payload, method);

        if (method == Method::ParityEven || method == Method::ParityOdd)
            cout << "Sender: parity bit = " << (unsigned)frame.back() << '\n';
        else {
            uint16_t trailer = (frame[frame.size()-2] << 8) | frame.back();
            ios::fmtflags f(cout.flags());
            cout << "Sender: trailer = 0x" << hex << uppercase << setw(4) << setfill('0') << trailer << dec << '\n';
            cout.flags(f);
        }

        cout << "Sender -> Frame (hex): ";
        printHex(frame);
        cout << '\n';

        cout << "\nInject error? (y/n): ";
        char yn = 'n';
        cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            cout << "Enter byte index to flip [0.." << (frame.size() - 1) << "]: ";
            size_t bidx = 0;
            cin >> bidx;
            cout << "Enter bit index to flip [0..7]: ";
            int bit = 0;
            cin >> bit;
            flipBit(frame, bidx, bit);
            cout << "Channel: flipped bit " << bit << " of byte " << bidx << '\n';
        }

        cout << "Channel -> Received frame (hex): ";
        printHex(frame);
        cout << '\n';

        vector<uint8_t> receivedPayload;
        bool ok = verifyFrame(frame, method, receivedPayload);

        cout << "Receiver: payload (hex): ";
        printHex(receivedPayload);
        cout << '\n';

        cout << "Receiver: error detected? " << (ok ? "No (OK)" : "Yes (CORRUPTED)") << '\n';

        cout << "\n---\n";
    }
    return 0;
}
 