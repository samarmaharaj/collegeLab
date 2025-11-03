#include <iostream>
#include <string>
#include <map>

using namespace std;

// --- ARP Simulation ---
// Simulates a node's ARP cache
map<string, string> arp_cache;
// Simulates the network's known hosts
map<string, string> network_hosts = {
    {"192.168.1.1", "AA:BB:CC:11:22:33"},
    {"192.168.1.2", "AA:BB:CC:44:55:66"}
};

string arp_request(string ip) {
    cout << "\n[ARP Request] Node 1: Who has IP " << ip << "? (Broadcast)\n";
    
    if (network_hosts.count(ip)) {
        string mac = network_hosts[ip];
        cout << "[ARP Reply] Node 2 (" << ip << "): I am at " << mac << " (Unicast)\n";
        // Add to cache
        arp_cache[ip] = mac;
        return mac;
    } else {
        cout << "[ARP] No reply for " << ip << "\n";
        return "";
    }
}

void simulate_arp() {
    cout << "--- Simulating ARP ---\n";
    string target_ip = "192.168.1.2";
    
    // 1. Check cache
    if (arp_cache.count(target_ip)) {
        cout << "Found in cache: " << target_ip << " -> " << arp_cache[target_ip] << "\n";
    } else {
        cout << "Not in cache. Sending ARP Request.\n";
        arp_request(target_ip);
    }
    
    // 2. Try again (now it should be in cache)
    cout << "\nSending packet to " << target_ip << "...\n";
     if (arp_cache.count(target_ip)) {
        cout << "Found in cache: " << target_ip << " -> " << arp_cache[target_ip] << "\n";
    } else {
        // ...
    }
}

// --- RARP Simulation ---
// Simulates a RARP server's table
map<string, string> rarp_table = {
    {"AA:BB:CC:77:88:99", "192.168.1.100"}
};

void rarp_request(string mac) {
    cout << "\n--- Simulating RARP ---\n";
    cout << "[RARP Request] Client (" << mac << "): What is my IP? (Broadcast)\n";
    
    if (rarp_table.count(mac)) {
        string ip = rarp_table[mac];
        cout << "[RARP Reply] Server: Your IP is " << ip << " (Unicast)\n";
    } else {
        cout << "[RARP] No server replied.\n";
    }
}

int main() {
    simulate_arp();
    rarp_request("AA:BB:CC:77:88:99"); // A MAC known by the RARP server
    return 0;
}
