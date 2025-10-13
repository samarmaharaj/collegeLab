#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

map<string, vector<vector<string>>> grammar;
map<string, set<string>> firstSets;
map<string, set<string>> followSets;

set<string> terminals;
set<string> nonTerminals;

const string EPSILON = "ε";
const string END_MARKER = "$";

// Utility to check if symbol is terminal
bool isTerminal(const string& symbol) {
    // If it's not a non-terminal, treat as terminal
    return nonTerminals.find(symbol) == nonTerminals.end();
}

// Compute First of a symbol
set<string> computeFirst(const string& symbol);

// Compute First of a production (list of symbols)
set<string> firstOfProduction(const vector<string>& production) {
    set<string> result;
    bool containsEpsilon = true;

    for (const auto& sym : production) {
        set<string> firstSym = computeFirst(sym);
        // Add all except epsilon
        for (const auto& f : firstSym) {
            if (f != EPSILON)
                result.insert(f);
        }
        if (firstSym.find(EPSILON) == firstSym.end()) {
            containsEpsilon = false;
            break;
        }
    }
    if (containsEpsilon) {
        result.insert(EPSILON);
    }
    return result;
}

// Compute First set for symbol
set<string> computeFirst(const string& symbol) {
    // If terminal, first is itself
    if (isTerminal(symbol)) {
        return {symbol};
    }
    // If already computed, return it
    if (firstSets.count(symbol) && !firstSets[symbol].empty()) {
        return firstSets[symbol];
    }

    // To handle recursion, we initially add an empty set for the symbol
    firstSets[symbol] = {};
    set<string> first;
    for (const auto& production : grammar[symbol]) {
        // If production is epsilon
        if (production.size() == 1 && production[0] == EPSILON) {
            first.insert(EPSILON);
        } else {
            set<string> firstProd = firstOfProduction(production);
            first.insert(firstProd.begin(), firstProd.end());
        }
    }

    firstSets[symbol] = first;
    return first;
}

// Compute Follow sets
void computeFollow() {
    // Initialize Follow sets empty
    for (const auto& nt : nonTerminals) {
        followSets[nt] = {};
    }
    // Add end marker to start symbol's Follow set
    followSets["E"].insert(END_MARKER);

    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& pair : grammar) {
            const string& lhs = pair.first;
            const vector<vector<string>>& productions = pair.second;
            for (const auto& production : productions) {
                for (size_t i = 0; i < production.size(); i++) {
                    string B = production[i];
                    if (nonTerminals.find(B) != nonTerminals.end()) {
                        set<string> followBefore = followSets[B];
                        // Look ahead symbols after B
                        set<string> firstOfBeta;
                        bool betaHasEpsilon = true;

                        // Beta = symbols after B in production
                        if (i + 1 < production.size()) {
                            vector<string> beta(production.begin() + i + 1, production.end());
                            firstOfBeta = firstOfProduction(beta);
                            if (firstOfBeta.find(EPSILON) != firstOfBeta.end()) {
                                betaHasEpsilon = true;
                                firstOfBeta.erase(EPSILON);
                            } else {
                                betaHasEpsilon = false;
                            }
                            // Add First(beta) \ {ε} to Follow(B)
                            followSets[B].insert(firstOfBeta.begin(), firstOfBeta.end());
                        } else {
                            betaHasEpsilon = true;
                        }
                        if (betaHasEpsilon) {
                            // Add Follow(lhs) to Follow(B)
                            followSets[B].insert(followSets[lhs].begin(), followSets[lhs].end());
                        }
                        if (followSets[B] != followBefore) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Define grammar
    grammar["E"] = {{"A", "B", "C"}};
    grammar["A"] = {{"a"}, {EPSILON}};
    grammar["B"] = {{"b"}};
    grammar["C"] = {{"c"}, {EPSILON}};
   
    // Extract non-terminals and terminals
    for (const auto& pair : grammar) {
        const string& nt = pair.first;
        const vector<vector<string>>& prods = pair.second;
        nonTerminals.insert(nt);
        for (const auto& prod : prods) {
            for (const auto& sym : prod) {
                if (nonTerminals.find(sym) == nonTerminals.end() && sym != EPSILON) {
                    terminals.insert(sym);
                }
            }
        }
    }

    // Compute First sets for all non-terminals
    for (const auto& nt : nonTerminals) {
        computeFirst(nt);
    }

    // Compute Follow sets
    computeFollow();

    // Print First sets
    cout << "First sets:" << endl;
    for (const auto& nt : nonTerminals) {
        cout << "First(" << nt << ") = { ";
        for (const auto& f : firstSets[nt]) {
            cout << f << " ";
        }
        cout << "}" << endl;
    }

    cout << "\nFollow sets:" << endl;
    for (const auto& nt : nonTerminals) {
        cout << "Follow(" << nt << ") = { ";
        for (const auto& f : followSets[nt]) {
            cout << f << " ";
        }
        cout << "}" << endl;
    }

    return 0;
}