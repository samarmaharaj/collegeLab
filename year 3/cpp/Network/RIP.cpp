#include <iostream>
#include <vector>
#include <iomanip> // For setw

using namespace std;

#define INF 999

void print_table(int id, const vector<int>& table) {
    cout << "Router " << id << " table: [";
    for (size_t i = 0; i < table.size(); ++i) {
        if (table[i] == INF) cout << "INF ";
        else cout << table[i] << " ";
    }
    cout << "]\n";
}

int main() {
    cout << "--- Simulating RIP (Distance Vector) ---\n";
    // 3 Routers: R0, R1, R2
    // R0 --1-- R1 --2-- R2
    // Initial tables (dist to self, R1, R2)
    vector<int> r0_table = {0, 1, INF};
    vector<int> r1_table = {1, 0, 2};
    vector<int> r2_table = {INF, 2, 0};

    cout << "Initial state:\n";
    print_table(0, r0_table);
    print_table(1, r1_table);
    print_table(2, r2_table);

    // --- Simulation Step 1 ---
    cout << "\nSTEP 1: R0 and R2 send tables to R1\n";
    
    // R1 learns from R0:
    // New dist to R2 via R0 = cost(R1,R0) + R0's_dist_to_R2 = 1 + INF = INF
    // No change.
    
    // R1 learns from R2:
    // New dist to R0 via R2 = cost(R1,R2) + R2's_dist_to_R0 = 2 + INF = INF
    // No change.
    
    cout << "\nSTEP 2: R1 sends table to R0 and R2\n";
    
    // R0 learns from R1:
    // New dist to R2 via R1 = cost(R0,R1) + R1's_dist_to_R2 = 1 + 2 = 3
    bool r0_changed = false;
    if (r0_table[2] > r0_table[1] + r1_table[2]) {
        r0_table[2] = r0_table[1] + r1_table[2]; // Update
        r0_changed = true;
    }
    cout << (r0_changed ? "R0 updated table.\n" : "R0 table unchanged.\n");

    // R2 learns from R1:
    // New dist to R0 via R1 = cost(R2,R1) + R1's_dist_to_R0 = 2 + 1 = 3
    bool r2_changed = false;
     if (r2_table[0] > r2_table[1] + r1_table[0]) {
        r2_table[0] = r2_table[1] + r1_table[0]; // Update
        r2_changed = true;
    }
    cout << (r2_changed ? "R2 updated table.\n" : "R2 table unchanged.\n");

    cout << "\nFinal state (converged):\n";
    print_table(0, r0_table); // {0, 1, 3}
    print_table(1, r1_table); // {1, 0, 2}
    print_table(2, r2_table); // {3, 2, 0}
    
    return 0;
}
