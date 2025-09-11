#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

// Function to read entire content from file or return empty string if error
std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return "";
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Count full word occurrences using regex \b for word boundaries
int countWordOccurrences(const std::string &text, const std::string &word) {
    std::regex wordRegex("\\b" + word + "\\b");
    return std::distance(std::sregex_iterator(text.begin(), text.end(), wordRegex),
                         std::sregex_iterator());
}

// Count subsequence (substring) occurrences, including overlaps
int countSubsequenceOccurrences(const std::string &text, const std::string &subseq) {
    if (subseq.empty()) return 0;
    int count = 0;
    size_t pos = 0;
    while ((pos = text.find(subseq, pos)) != std::string::npos) {
        count++;
        pos++;  // move forward by one to allow overlaps
    }
    return count;
}

int main() {
    std::string choice;
    std::string text;
    std::cout << "Do you want to input text or read from file? (text/file): ";
    std::cin >> choice;
    std::cin.ignore(); // clear newline from input buffer

    if (choice == "file") {
        std::string filename;
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);
        text = readFile(filename);
        if (text.empty()) return 1; // stop if file read failed
    } else {
        std::cout << "Enter your text: ";
        std::getline(std::cin, text);
    }

    std::string searchTerm;
    std::cout << "Enter the word or subsequence to search: ";
    std::getline(std::cin, searchTerm);

    int wordCount = countWordOccurrences(text, searchTerm);
    int subseqCount = countSubsequenceOccurrences(text, searchTerm);

    std::cout << "\nResults:\n";
    std::cout << "Word occurrences: " << wordCount << "\n";
    std::cout << "Subsequence occurrences: " << subseqCount << "\n";

    return 0;
}
