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

// Function to check for direct left recursion in the grammar.
void checkLeftRecursion(const Grammar& grammar) {
    std::cout << "--- Checking for Direct Left Recursion ---\n";
    bool foundRecursion = false;

    for (const auto& rule : grammar) {
        char nt = rule.first;
        const std::vector<std::string>& prods = rule.second;

        for (const auto& prod : prods) {
            // A production is left-recursive if it's not empty and starts with its own non-terminal.
            if (!prod.empty() && prod[0] == nt) {
                std::cout << "Direct Left Recursion found in rule: " << nt << " -> " << prod << std::endl;
                foundRecursion = true;
            }
        }
    }

    if (!foundRecursion) {
        std::cout << "No direct left recursion found in the grammar.\n";
    }
    std::cout << "----------------------------------------\n\n";
}

// Function to check if the grammar needs left factoring.
void checkLeftFactoring(const Grammar& grammar) {
    std::cout << "--- Checking for Left Factoring ---\n";
    bool needsFactoring = false;

    for (const auto& rule : grammar) {
        char nt = rule.first;
        const std::vector<std::string>& prods = rule.second;

        // Factoring is only needed if there are 2 or more productions for a non-terminal.
        if (prods.size() < 2) {
            continue;
        }

        bool foundForNt = false;
        // Compare each pair of productions for a common prefix.
        for (size_t j = 0; j < prods.size() - 1; ++j) {
            for (size_t k = j + 1; k < prods.size(); ++k) {
                const std::string& s1 = prods[j];
                const std::string& s2 = prods[k];
                std::string commonPrefix = "";

                // Find the longest common prefix.
                for (size_t i = 0; i < std::min(s1.length(), s2.length()); ++i) {
                    if (s1[i] == s2[i]) {
                        commonPrefix += s1[i];
                    } else {
                        break;
                    }
                }

                if (!commonPrefix.empty()) {
                    std::cout << "Grammar needs Left Factoring for non-terminal '" << nt << "'.\n";
                    std::cout << "Common prefix '" << commonPrefix << "' found in productions:\n";
                    std::cout << "  - " << nt << " -> " << s1 << std::endl;
                    std::cout << "  - " << nt << " -> " << s2 << std::endl;
                    needsFactoring = true;
                    foundForNt = true;
                    break; // Move to the next non-terminal.
                }
            }
            if (foundForNt) {
                break;
            }
        }
    }

    if (!needsFactoring) {
        std::cout << "The grammar does not require left factoring.\n";
    }
    std::cout << "-------------------------------------\n\n";
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
        // Handle empty lines gracefully.
        if (line.empty()) continue;

        std::stringstream ss(line);
        char nonTerminal;
        std::string arrow, productions_str;
        
        ss >> nonTerminal >> arrow;
        
        // Read the rest of the line as the productions part.
        std::getline(ss, productions_str);
        
        std::stringstream prods_ss(productions_str);
        std::string single_production;
        // Split the right-hand side of the rule by the '|' delimiter.
        while (std::getline(prods_ss, single_production, '|')) {
            grammar[nonTerminal].push_back(trim(single_production));
        }
    }

    printGrammar(grammar, "Original Grammar");

    // Perform checks on the grammar.
    checkLeftRecursion(grammar);
    checkLeftFactoring(grammar);

    return 0;
}

