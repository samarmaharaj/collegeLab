#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    FILE* file_with_data = _popen("ipconfig /all", "r");
    if (!file_with_data) {
        cerr << "Failed to run command\n";
        return 1;
    }

    char bff[256];
    string curad;

    while (fgets(bff, sizeof(bff), file_with_data)) {
        string line(bff);

        if (line.find(":") != string::npos && line.find("adapter") != string::npos) {
            curad = line.substr(0, line.find(":"));
            while (!curad.empty() && isspace(curad.back()))
                curad.pop_back();
        }

        if (line.find("Physical Address") != string::npos) {
            cout << "[" << curad << "] "
                 << "MAC Address: " << line.substr(line.find(":") + 2);
        }

        if (line.find("IPv4 Address") != string::npos) {
            string ip = line.substr(line.find(":") + 2);
            size_t pos = ip.find("(");
            if (pos != string::npos)
                ip = ip.substr(0, pos);
            cout << "[" << curad << "] "
                 << "IP Address: " << ip << endl;
        }

        if (line.find("IPv6 Address") != string::npos) {
            string ip = line.substr(line.find(":") + 2);
            size_t pos = ip.find("(");
            if (pos != string::npos)
                ip = ip.substr(0, pos);
            cout << "[" << curad << "] "
                 << "IPv6 Address: " << ip << endl;
        }
    }

    _pclose(file_with_data);
    return 0;
}
