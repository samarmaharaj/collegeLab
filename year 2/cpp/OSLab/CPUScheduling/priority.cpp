#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;      
    int burstTime; 
    int priority;  
    int waitingTime;
    int turnAroundTime; 
};


bool comparePriority(Process a, Process b) {
    return a.priority < b.priority;
}

void calculateWaitingTime(vector<Process>& processes) {
    processes[0].waitingTime = 0;  // First process has no waiting time

    for (size_t i = 1; i < processes.size(); i++) {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnAroundTime(vector<Process>& processes) {
    for (size_t i = 0; i < processes.size(); i++) {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void calculateAverageTimes(const vector<Process>& processes) {
    int totalWaitingTime = 0;
    int totalTurnAroundTime = 0;

    for (const auto& process : processes) {
        totalWaitingTime += process.waitingTime;
        totalTurnAroundTime += process.turnAroundTime;
    }

    cout << "Average Waiting Time: " << (float)totalWaitingTime / processes.size() << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnAroundTime / processes.size() << endl;
}

void printProcessDetails(const vector<Process>& processes) {
    cout << "PID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" << process.burstTime << "\t\t" << process.priority << "\t\t" << process.waitingTime << "\t\t" << process.turnAroundTime << "\n";
    }
}

int main() {
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        processes[i].pid = i + 1;
        cout << "Enter burst time for process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << processes[i].pid << ": ";
        cin >> processes[i].priority;
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
    }

    sort(processes.begin(), processes.end(), comparePriority);


    calculateWaitingTime(processes);
    calculateTurnAroundTime(processes);

    printProcessDetails(processes);

    calculateAverageTimes(processes);

    return 0;
}