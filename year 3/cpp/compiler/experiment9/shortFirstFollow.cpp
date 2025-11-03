#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

// Using statements for brevity
using namespace std;

// --- Global Definitions ---
map<string, vector<vector<string>>> grammar;
map<string, set<string>> firstSets, followSets;
set<string> nonTerminals;
const string EPSILON = "e"; // Using 'e' for epsilon for simplicity
const string END_MARKER = "$";

// --- Forward Declaration ---
set<string> computeFirst(const string& symbol);

// --- Helper Functions ---
bool isTerminal(const string& symbol) {
    return nonTerminals.find(symbol) == nonTerminals.end();
}

// Generic function to print the computed sets
void printSet(const map<string, set<string>>& sets, const string& name) {
    cout << "--- " << name << " Sets ---\n";
    // Using C++11 compatible loop instead of structured bindings
    for (const auto& pair : sets) {
        const string& nt = pair.first;
        const set<string>& s = pair.second;
        cout << name << "(" << nt << ") = { ";
        string temp;
        for (const auto& item : s) temp += item + " ";
        if (!temp.empty()) temp.pop_back(); // Remove trailing space
        cout << temp << " }\n";
    }
    cout << endl;
}

// --- Core Logic ---
set<string> firstOfProduction(const vector<string>& production) {
    set<string> result;
    bool allHaveEpsilon = true;
    for (const auto& sym : production) {
        set<string> firstOfSym = computeFirst(sym);
        bool hasEpsilon = firstOfSym.count(EPSILON);
        
        if (!hasEpsilon) allHaveEpsilon = false;
        
        firstOfSym.erase(EPSILON);
        result.insert(firstOfSym.begin(), firstOfSym.end());
        
        if (!hasEpsilon) break;
    }
    if (allHaveEpsilon) result.insert(EPSILON);
    return result;
}

set<string> computeFirst(const string& symbol) {
    if (isTerminal(symbol)) return {symbol};
    // Return memoized result if already computed
    if (firstSets.count(symbol) && !firstSets[symbol].empty()) return firstSets[symbol];
    
    firstSets[symbol] = {}; // Mark as "in progress" to handle recursion
    set<string> first;
    for (const auto& production : grammar[symbol]) {
        set<string> firstProd = firstOfProduction(production);
        first.insert(firstProd.begin(), firstProd.end());
    }
    return firstSets[symbol] = first; // Memoize and return
}

void computeFollowSets(const string& startSymbol) {
    for (const auto& nt : nonTerminals) followSets[nt] = {};
    followSets[startSymbol].insert(END_MARKER);

    bool changed = true;
    while (changed) {
        changed = false;
        // Using C++11 compatible loop instead of structured bindings
        for (const auto& pair : grammar) {
            const string& lhs = pair.first;
            const vector<vector<string>>& productions = pair.second;
            for (const auto& production : productions) {
                for (size_t i = 0; i < production.size(); ++i) {
                    if (isTerminal(production[i])) continue;
                    
                    const string& B = production[i];
                    size_t prev_size = followSets[B].size();
                    
                    vector<string> beta(production.begin() + i + 1, production.end());
                    set<string> firstOfBeta = firstOfProduction(beta);
                    
                    if (firstOfBeta.count(EPSILON)) {
                        followSets[B].insert(followSets[lhs].begin(), followSets[lhs].end());
                        firstOfBeta.erase(EPSILON);
                    }
                    followSets[B].insert(firstOfBeta.begin(), firstOfBeta.end());
                    
                    if (followSets[B].size() != prev_size) changed = true;
                }
            }
        }
    }
}

// --- Main Execution ---
int main() {
    // A standard grammar for arithmetic expressions
    grammar["E"] = {{"T", "E'"}};
    grammar["E'"] = {{"+", "T", "E'"}, {EPSILON}};
    grammar["T"] = {{"F", "T'"}};
    grammar["T'"] = {{"*", "F", "T'"}, {EPSILON}};
    grammar["F"] = {{"(", "E", ")"}, {"id"}};
    const string startSymbol = "E";

    // Automatically populate non-terminals from grammar keys
    for (const auto& rule : grammar) nonTerminals.insert(rule.first);
    
    // Compute and display results
    for (const auto& nt : nonTerminals) computeFirst(nt);
    computeFollowSets(startSymbol);

    printSet(firstSets, "First");
    printSet(followSets, "Follow");

    return 0;
}

