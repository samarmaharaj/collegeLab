#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> burstTime = {10, 6, 2, 4};
    vector<int> arrivalTime = {0, 1, 3, 5};

    int n = burstTime.size();
    vector<int> finishTime(n, 0);
    vector<int> waitingTime(n, 0);
    vector<int> turnAroundTime(n, 0);
    finishTime[0] = burstTime[0];
    for (int i = 1; i < n; i++) {
        finishTime[i] = finishTime[i - 1] + burstTime[i];
    }

    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = finishTime[i] - arrivalTime[i];
        waitingTime[i] = turnAroundTime[i] - burstTime[i];
    }

    cout << "Process\tBurst Time\tArrival Time\tCompletion Time\tWaiting Time\tTurn Around Time" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << "\t" << arrivalTime[i] << "\t\t" << burstTime[i] << "\t\t" << finishTime[i] << "\t\t" << turnAroundTime[i] << "\t\t" << waitingTime[i] << endl;
    }

    cout << "Average Waiting Time: " << accumulate(waitingTime.begin(), waitingTime.end(), 0) / n << endl;
    cout << "Average Turn Around Time: " << accumulate(turnAroundTime.begin(), turnAroundTime.end(), 0) / n << endl;

    return 0;
}