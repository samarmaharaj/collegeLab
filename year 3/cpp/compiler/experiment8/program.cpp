#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

// Use a map to represent the grammar.
// The key is the non-terminal (char) and the value is a vector of its productions (strings).
using Grammar = std::map<char, std::vector<std::string>>;

// A utility function to print the grammar in a readable format.
void printGrammar(const Grammar& grammar, const std::string& title) {
    std::cout << "--- " << title << " ---\n";
    for (const auto& rule : grammar) {
        std::cout << rule.first << " -> ";
        for (size_t i = 0; i < rule.second.size(); ++i) {
            // Use '^' to represent epsilon (empty string) for clarity.
            std::cout << (rule.second[i].empty() ? "^" : rule.second[i])
                      << (i == rule.second.size() - 1 ? "" : " | ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to eliminate direct left recursion from the grammar.
void removeDirectLeftRecursion(Grammar& grammar) {
    // A character to use for new non-terminals. We start from 'Z' and go backwards.
    char newNonTerminal = 'Z';
    
    // We need to iterate over a copy of the keys because we might modify the grammar map inside the loop.
    std::vector<char> nonTerminals;
    for (const auto& pair : grammar) {
        nonTerminals.push_back(pair.first);
    }

    for (char nt : nonTerminals) {
        std::vector<std::string> recursiveProds;
        std::vector<std::string> nonRecursiveProds;

        // Separate productions into recursive (starting with the non-terminal itself) and non-recursive.
        for (const auto& prod : grammar[nt]) {
            if (prod[0] == nt) {
                recursiveProds.push_back(prod.substr(1));
            } else {
                nonRecursiveProds.push_back(prod);
            }
        }

        // If there are no recursive productions for this non-terminal, continue to the next one.
        if (recursiveProds.empty()) {
            continue;
        }

        // Generate a new non-terminal character, ensuring it's not already in the grammar.
        while (grammar.count(newNonTerminal)) {
            newNonTerminal--;
        }

        // 1. Replace the original productions for the non-terminal 'nt'.
        // The new productions will be of the form: A -> betaA'
        grammar[nt].clear();
        for (const auto& beta : nonRecursiveProds) {
            // Handle the case where a beta might be epsilon (empty)
            if (beta.empty()) {
                 grammar[nt].push_back(std::string(1, newNonTerminal));
            } else {
                 grammar[nt].push_back(beta + newNonTerminal);
            }
        }

        // 2. Create new productions for the new non-terminal.
        // The new productions will be of the form: A' -> alphaA' | epsilon
        for (const auto& alpha : recursiveProds) {
            grammar[newNonTerminal].push_back(alpha + newNonTerminal);
        }
        // Add the epsilon production.
        grammar[newNonTerminal].push_back(""); // "" represents epsilon
    }
}


// Function to perform left factoring on the grammar.
void leftFactor(Grammar& grammar) {
    char newNonTerminal = 'Y';
    bool changed;

    do {
        changed = false;
        std::vector<char> nonTerminals;
        for (const auto& pair : grammar) {
            nonTerminals.push_back(pair.first);
        }
        
        for (char nt : nonTerminals) {
            std::vector<std::string>& prods = grammar[nt];
            if (prods.size() <= 1) continue;

            // Sort productions to easily find common prefixes among adjacent elements.
            std::sort(prods.begin(), prods.end());

            std::string prefix = "";
            int groupStartIndex = -1;
            
            // Find the first group of productions with a common prefix.
            for (size_t i = 0; i < prods.size() - 1; ++i) {
                const std::string& p1 = prods[i];
                const std::string& p2 = prods[i+1];
                std::string currentPrefix = "";
                for (size_t k = 0; k < std::min(p1.length(), p2.length()); ++k) {
                    if (p1[k] == p2[k]) {
                        currentPrefix += p1[k];
                    } else {
                        break;
                    }
                }
                if (!currentPrefix.empty()) {
                    prefix = currentPrefix;
                    groupStartIndex = i;
                    break;
                }
            }

            // If a common prefix was found, perform factoring.
            if (!prefix.empty()) {
                changed = true;
                
                std::vector<std::string> toFactor;
                std::vector<std::string> remaining;

                // Separate the productions into those that need factoring and those that don't.
                for (const auto& p : prods) {
                    if (p.rfind(prefix, 0) == 0) { // C++20 has starts_with
                        toFactor.push_back(p);
                    } else {
                        remaining.push_back(p);
                    }
                }

                // Generate a new non-terminal character.
                while (grammar.count(newNonTerminal)) {
                    newNonTerminal--;
                }
                
                // 1. Update the original non-terminal's productions.
                remaining.push_back(prefix + newNonTerminal);
                grammar[nt] = remaining;
                
                // 2. Create productions for the new non-terminal.
                for (const auto& p : toFactor) {
                    grammar[newNonTerminal].push_back(p.substr(prefix.length()));
                }
                
                // Break from the loop over non-terminals to restart the process,
                // as the grammar has changed.
                break; 
            }
        }
    } while (changed);
}

// Helper function to trim whitespace from both ends of a string.
std::string trim(const std::string& str) {
    const std::string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content, all whitespace

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


int main() {
    Grammar grammar;
    std::string line;

    std::cout << "Enter grammar rules (e.g., E->E+T|T). Type 'END' to finish:\n";
    
    // --- Input Processing ---
    while (std::getline(std::cin, line) && line != "END") {
        std::stringstream ss(line);
        char nonTerminal;
        std::string arrow, production;
        
        ss >> nonTerminal >> arrow;
        
        // Split the right-hand side of the rule by the '|' delimiter.
        while (std::getline(ss, production, '|')) {
            grammar[nonTerminal].push_back(trim(production));
        }
    }

    printGrammar(grammar, "Original Grammar");

    removeDirectLeftRecursion(grammar);
    printGrammar(grammar, "Grammar After Removing Left Recursion");

    leftFactor(grammar);
    printGrammar(grammar, "Grammar After Left Factoring");

    return 0;
}

