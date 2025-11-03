#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Represents a path (a list of AS numbers)
using Path = vector<int>;

// A BGP routing table entry
struct Route {
    string prefix;
    Path path;
    int nextHop;
};

void print_table(int as_id, const map<string, Route>& table) {
    cout << "--- BGP Table for AS" << as_id << " ---\n";
    for (auto const& [prefix, route] : table) {
        cout << "Prefix: " << prefix << " | Next-Hop: AS" << route.nextHop << " | Path: ";
        for (int as : route.path) {
            cout << as << " ";
        }
        cout << "\n";
    }
}

int main() {
    cout << "--- Simulating BGP (Path Vector) ---\n";
    // 3 ASes: AS1, AS2, AS3
    // AS1 originates prefix 10.0.0.0/8
    // AS1 -- AS2 -- AS3
    
    map<string, Route> as1_table;
    map<string, Route> as2_table;
    map<string, Route> as3_table;

    // 1. AS1 advertises its own prefix
    as1_table["10.0.0.0/8"] = {"10.0.0.0/8", {1}, 0}; // 0 = self
    cout << "AS1 originates 10.0.0.0/8\n";
    print_table(1, as1_table);

    // 2. AS1 advertises to AS2
    cout << "\nAS1 advertises to AS2\n";
    Path p_from_1 = as1_table["10.0.0.0/8"].path;
    p_from_1.insert(p_from_1.begin(), 2); // AS2 prepends its own AS
    as2_table["10.0.0.0/8"] = {"10.0.0.0/8", p_from_1, 1}; // Next-hop is AS1
    print_table(2, as2_table);

    // 3. AS2 advertises to AS3
    cout << "\nAS2 advertises to AS3\n";
    Path p_from_2 = as2_table["10.0.0.0/8"].path;
    p_from_2.insert(p_from_2.begin(), 3); // AS3 prepends its own AS
    as3_table["10.0.0.0/8"] = {"10.0.0.0/8", p_from_2, 2}; // Next-hop is AS2
    print_table(3, as3_table);
    
    // 4. Check AS3's path to 10.0.0.0/8
    cout << "\nAS3's best path to 10.0.0.0/8 is: ";
    for (int as : as3_table["10.0.0.0/8"].path) {
        cout << "AS" << as << " ";
    }
    cout << "\n(Policy: Shortest AS-PATH length)\n";
    
    return 0;
}
