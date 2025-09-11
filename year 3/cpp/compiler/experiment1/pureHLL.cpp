#include <iostream>
#include <sstream>
#include <unordered_map>
#include <regex>
using namespace std;

std::string removeComments(const std::string& code) {
    // Remove single-line comments
    std::string noSingleLine = std::regex_replace(code, std::regex("//.*"), "");
    // Remove multi-line comments using [\s\S] to match across newlines
    std::string noMultiLine = std::regex_replace(noSingleLine, std::regex("/\\*[\\s\\S]*?\\*/"), "");
    return noMultiLine;
}


std::unordered_map<std::string, std::string> extractMacros(std::istringstream& stream) {
    std::unordered_map<std::string, std::string> macros;
    std::string line;
    std::regex defineRegex(R"(#define\s+(\w+)\s+(.*))");

    while (std::getline(stream, line)) {
        std::smatch match;
        if (std::regex_search(line, match, defineRegex)) { // use regex_search
            macros[match[1]] = match[2];
        }
    }
    return macros;
}

std::string preprocess(const std::string& rawCode) {
    std::string cleanedCode = removeComments(rawCode);
    std::istringstream stream(cleanedCode);
    std::unordered_map<std::string, std::string> macros = extractMacros(stream);

    // Step 1: Extract string literals
    std::vector<std::string> stringLiterals;
    std::string tempCode = cleanedCode;
    std::regex stringRegex(R"("([^"\\]|\\.)*")"); // Matches "..." strings with escapes
    std::smatch match;

    while (std::regex_search(tempCode, match, stringRegex)) {
        stringLiterals.push_back(match.str());
        tempCode.replace(match.position(), match.length(), "___STR_PLACEHOLDER_" + std::to_string(stringLiterals.size() - 1) + "___");
    }

    // Step 2: Process macros on tempCode (no strings now)
    std::istringstream finalStream(tempCode);
    std::ostringstream output;
    std::string line;
    std::regex defineLine(R"(#define\s+.*)");

    while (std::getline(finalStream, line)) {
        if (std::regex_search(line, defineLine)) continue; // Skip macro definitions

        bool replaced;
        do {
            replaced = false;
            for (auto it = macros.begin(); it != macros.end(); ++it) {
                std::regex macroRegex("\\b" + it->first + "\\b");
                std::string newLine = std::regex_replace(line, macroRegex, it->second);
                if (newLine != line) {
                    replaced = true;
                    line = newLine;
                }
            }
        } while (replaced);

        output << line << "\n";
    }

    // Step 3: Restore string literals
    std::string finalCode = output.str();
    for (size_t i = 0; i < stringLiterals.size(); ++i) {
        std::string placeholder = "___STR_PLACEHOLDER_" + std::to_string(i) + "___";
        finalCode = std::regex_replace(finalCode, std::regex(placeholder), stringLiterals[i]);
    }

    return finalCode;
}


int main() {
    string input = R"(#include <iostream>
#define PI 3.14
#define MSG "Hello, World!"

int main() {
    // Print message
    /* This is multi-line
    comment */
    std::cout << MSG << std::endl;
    std::cout << "Value of PI: " << PI << std::endl;
    return 0;
}
)";

    string output = preprocess(input);
    cout << output;
    return 0;
}
