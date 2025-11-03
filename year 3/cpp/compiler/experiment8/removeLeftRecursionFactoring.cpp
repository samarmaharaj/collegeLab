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
            std::cout << (rule.second[i].empty() ? "^" : rule.second[i])
                      << (i == rule.second.size() - 1 ? "" : " | ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function to eliminate direct left recursion from the grammar.
void removeDirectLeftRecursion(Grammar& grammar) {
    char newNonTerminal = 'Z';
    std::vector<char> nonTerminals;
    for (const auto& pair : grammar) {
        nonTerminals.push_back(pair.first);
    }

    for (char nt : nonTerminals) {
        std::vector<std::string> recursiveProds, nonRecursiveProds;

        for (const auto& prod : grammar[nt]) {
            if (!prod.empty() && prod[0] == nt) {
                recursiveProds.push_back(prod.substr(1));
            } else {
                nonRecursiveProds.push_back(prod);
            }
        }

        if (recursiveProds.empty()) continue;

        while (grammar.count(newNonTerminal)) newNonTerminal--;
        
        grammar[nt].clear();
        for (const auto& beta : nonRecursiveProds) {
            grammar[nt].push_back((beta.empty() ? "" : beta) + newNonTerminal);
        }

        for (const auto& alpha : recursiveProds) {
            grammar[newNonTerminal].push_back(alpha + newNonTerminal);
        }
        grammar[newNonTerminal].push_back(""); // Epsilon production
    }
}

// Function to perform left factoring on the grammar.
void leftFactor(Grammar& grammar) {
    char newNonTerminal = 'Y';
    bool changed;
    do {
        changed = false;
        std::vector<char> nonTerminals;
        for (const auto& pair : grammar) nonTerminals.push_back(pair.first);
        
        for (char nt : nonTerminals) {
            std::vector<std::string>& prods = grammar[nt];
            if (prods.size() <= 1) continue;

            std::sort(prods.begin(), prods.end());
            std::string prefix = "";
            
            for (size_t i = 0; i < prods.size() - 1; ++i) {
                std::string currentPrefix = "";
                const std::string& p1 = prods[i];
                const std::string& p2 = prods[i+1];
                for (size_t k = 0; k < std::min(p1.length(), p2.length()) && p1[k] == p2[k]; ++k) {
                    currentPrefix += p1[k];
                }
                if (!currentPrefix.empty()) {
                    prefix = currentPrefix;
                    break;
                }
            }

            if (!prefix.empty()) {
                changed = true;
                std::vector<std::string> toFactor, remaining;
                for (const auto& p : prods) {
                    if (p.rfind(prefix, 0) == 0) toFactor.push_back(p);
                    else remaining.push_back(p);
                }

                while (grammar.count(newNonTerminal)) newNonTerminal--;
                
                remaining.push_back(prefix + newNonTerminal);
                grammar[nt] = remaining;
                
                for (const auto& p : toFactor) {
                    grammar[newNonTerminal].push_back(p.substr(prefix.length()));
                }
                break; 
            }
        }
    } while (changed);
}

// Helper function to trim whitespace from both ends of a string.
std::string trim(const std::string& str) {
    const std::string whitespace = " \t";
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

int main() {
    Grammar grammar;
    std::string line;

    std::cout << "Enter grammar rules (e.g., E->E+T|T). Type 'END' to finish:\n";
    
    while (std::getline(std::cin, line) && line != "END") {
        if (line.empty()) continue;

        std::stringstream ss(line);
        char nonTerminal;
        std::string arrow, productions_str;
        
        ss >> nonTerminal >> arrow;
        std::getline(ss, productions_str);
        
        std::stringstream prods_ss(productions_str);
        std::string single_production;
        while (std::getline(prods_ss, single_production, '|')) {
            grammar[nonTerminal].push_back(trim(single_production));
        }
    }

    printGrammar(grammar, "Original Grammar");
    removeDirectLeftRecursion(grammar);
    printGrammar(grammar, "Grammar After Removing Left Recursion");
    leftFactor(grammar);
    printGrammar(grammar, "Grammar After Left Factoring");

    return 0;
}

