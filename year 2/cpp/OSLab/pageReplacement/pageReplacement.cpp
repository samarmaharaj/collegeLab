#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Function to implement FIFO Page Replacement
int fifoPageReplacement(const vector<int>& pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : pages) {
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() == capacity) {
                memory.erase(memory.begin());
            }
            memory.push_back(page);
            pageFaults++;
        }
    }
    return pageFaults;
}

// Function to implement LRU Page Replacement
int lruPageReplacement(const vector<int>& pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;

    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            if (memory.size() == capacity) {
                memory.erase(memory.begin());
            }
            pageFaults++;
        } else {
            memory.erase(it);
        }
        memory.push_back(page);
    }
    return pageFaults;
}

// Function to implement Optimal Page Replacement
int optimalPageReplacement(const vector<int>& pages, int capacity) {
    vector<int> memory;
    int pageFaults = 0;

    for (size_t i = 0; i < pages.size(); ++i) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            if (memory.size() == capacity) {
                int farthest = i, index = -1;
                for (size_t j = 0; j < memory.size(); ++j) {
                    auto it = find(pages.begin() + i + 1, pages.end(), memory[j]);
                    if (it == pages.end()) {
                        index = j;
                        break;
                    } else if (distance(pages.begin(), it) > farthest) {
                        farthest = distance(pages.begin(), it);
                        index = j;
                    }
                }
                memory.erase(memory.begin() + index);
            }
            memory.push_back(page);
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int capacity = 3;

    cout << "FIFO Page Faults: " << fifoPageReplacement(pages, capacity) << endl;
    cout << "LRU Page Faults: " << lruPageReplacement(pages, capacity) << endl;
    cout << "Optimal Page Faults: " << optimalPageReplacement(pages, capacity) << endl;

    return 0;
}