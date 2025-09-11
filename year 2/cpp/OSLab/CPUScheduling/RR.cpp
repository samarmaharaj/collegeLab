#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int pid;       
    int burstTime;  
    int remainingTime; 
    int waitingTime;
    int turnAroundTime; 
};

void calculateWaitingTime(vector<Process>& processes, int quantum) {
    queue<Process*> processQueue;
    for (auto& process : processes) {
        processQueue.push(&process);
    }

    int currentTime = 0;

    while (!processQueue.empty()) {
        Process* currentProcess = processQueue.front();
        processQueue.pop();

        if (currentProcess->remainingTime > quantum) {
            currentTime += quantum;
            currentProcess->remainingTime -= quantum;
            processQueue.push(currentProcess);
        } else {
            currentTime += currentProcess->remainingTime;
            currentProcess->waitingTime = currentTime - currentProcess->burstTime;
            currentProcess->remainingTime = 0;
        }
    }
}

void calculateTurnAroundTime(vector<Process>& processes) {
    for (auto& process : processes) {
        process.turnAroundTime = process.burstTime + process.waitingTime;
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
    cout << "PID\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.pid << "\t" << process.burstTime << "\t\t" << process.waitingTime << "\t\t" << process.turnAroundTime << "\n";
    }
}

int main() {
    int numProcesses;
    int quantum;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    cout << "Enter the time quantum: ";
    cin >> quantum;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        processes[i].pid = i + 1;
        cout << "Enter burst time for process " << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnAroundTime = 0;
    }

    calculateWaitingTime(processes, quantum);
    calculateTurnAroundTime(processes);

    printProcessDetails(processes);
    calculateAverageTimes(processes);

    return 0;
}