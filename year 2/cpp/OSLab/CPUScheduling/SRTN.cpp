#include <bits/stdc++.h>
using namespace std;

void sortProcesses(vector<int>& remainingTime, int num) {
    remainingTime.push_back(num);
    sort(remainingTime.begin(), remainingTime.end());
}

void decrement(vector<int>& remainingTime, int num, int &flag) {
    for (int i = 0; i < num; i++) {
        remainingTime[0]--;
    }

    flag += num;
    if (remainingTime[0] == 0) {
        remainingTime.erase(remainingTime.begin());
        // finishTime[0] += num;
    }
}

int main() {
    // vector<int> burstTime = {10, 6, 2, 4};
    vector<pair<int, int>> arrivalTime = {{0,10}, {1,6}, {3,2}, {5, 4}};
    int n = arrivalTime.size();

    vector<int> remainingTime;

    vector<int> finishTime(n, 0);

    int flag = 0;

    // while(true) {
        sortProcesses(remainingTime, arrivalTime[0].second);
        decrement(remainingTime, 1, flag);
        sortProcesses(remainingTime, arrivalTime[1].second);
        decrement(remainingTime, 2, flag);
        sortProcesses(remainingTime, arrivalTime[2].second);
        decrement(remainingTime, 2, flag);
        sortProcesses(remainingTime, arrivalTime[3].second);
        decrement(remainingTime, 4, flag);
        decrement(remainingTime, 4, flag);
        decrement(remainingTime, 9, flag);

        cout << "Remaining Time: " << remainingTime.empty() << endl; 
        cout << "Total Time: " << flag << endl;

    return 0;
}