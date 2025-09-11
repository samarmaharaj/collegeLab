#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>
#include <regex>

// --- Function to execute a system command and get its output ---
// This is a helper function to run a command and capture what it prints.
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    // Use std::unique_ptr for automatic memory management of the pipe
    #ifdef _WIN32
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
    #else
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    #endif
    
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    // Read the output from the command
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int main() {
    std::string command_output;
    
    // --- Determine the OS and set the correct command ---
    #ifdef _WIN32
        // Command for Windows
        const char* command = "ipconfig /all";
    #else
        // Command for macOS and Linux
        const char* command = "ifconfig";
    #endif

    try {
        // Execute the command and store the output
        command_output = exec(command);
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "Please ensure '" << command << "' is a valid command on your system." << std::endl;
        return 1;
    }

    // --- Use Regular Expressions to find IP and MAC addresses ---
    // Regex for IPv4 Address
    std::regex ipv4_regex("(\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b)");
    // Regex for MAC Address
    std::regex mac_regex("([0-9a-fA-F]{2}[:-]){5}([0-9a-fA-F]{2})");

    std::smatch match;

    std::cout << "🔍 Searching for network information..." << std::endl;
    
    // --- Find and print the IPv4 address ---
    if (std::regex_search(command_output, match, ipv4_regex)) {
        // We often find 127.0.0.1 first, so we can search again to find the real one
        // This is a simple way to skip the loopback address
        std::string temp_output = match.suffix().str();
        if (match.str(1) == "127.0.0.1" && std::regex_search(temp_output, match, ipv4_regex)) {
             std::cout << "  IPv4 Address: " << match.str(1) << std::endl;
        } else {
             std::cout << "  IPv4 Address: " << match.str(1) << std::endl;
        }
    } else {
        std::cout << "  IPv4 Address: Not found" << std::endl;
    }

    // --- Find and print the MAC address ---
    if (std::regex_search(command_output, match, mac_regex)) {
        std::cout << "  MAC Address:  " << match.str(0) << std::endl;
    } else {
        std::cout << "  MAC Address:  Not found" << std::endl;
    }

    return 0;
}
