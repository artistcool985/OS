//All CPU scheduling
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>

using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;

    Process(int _id, int _arrival_time, int _burst_time, int _priority = 0) {
        id = _id;
        arrival_time = _arrival_time;
        burst_time = _burst_time;
        priority = _priority;
        completion_time = 0;
        turnaround_time = 0;
        waiting_time = 0;
        remaining_time = _burst_time;
    }
};

void fcfs(vector<Process>& processes) {
    int currentTime = 0;
    for (Process& p : processes) {
        if (p.arrival_time > currentTime)
            currentTime = p.arrival_time;
        currentTime += p.burst_time;
        p.completion_time = currentTime;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
    }
}

void sjfNP(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0, completed = 0;
    vector<bool> isCompleted(n, false);

    while (completed != n) {
        int minBurst = INT_MAX, shortest = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= currentTime && !isCompleted[i] && processes[i].burst_time < minBurst) {
                minBurst = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest != -1) {
            currentTime += processes[shortest].burst_time;
            processes[shortest].completion_time = currentTime;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            isCompleted[shortest] = true;
            completed++;
        } else {
            currentTime++;
        }
    }
}

bool compareArrival(const Process& a, const Process& b) {
    return a.arrival_time < b.arrival_time;
}

void sjfPreemptive(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), compareArrival);

    int n = processes.size();
    vector<int> remainingTime(n);
    for (int i = 0; i < n; ++i)
        remainingTime[i] = processes[i].burst_time;

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int minRemaining = INT_MAX;
        int shortest = -1;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= currentTime && remainingTime[i] < minRemaining && remainingTime[i] > 0) {
                minRemaining = remainingTime[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
            continue;
        }

        remainingTime[shortest]--;
        if (remainingTime[shortest] == 0) {
            completed++;
            processes[shortest].completion_time = currentTime + 1;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
        }
        currentTime++;
    }
}

void roundRobin(vector<Process>& processes, int timeQuantum) {
    int currentTime = 0;
    int n = processes.size();
    vector<int> remainingBurstTime(n);
    for (int i = 0; i < n; ++i)
        remainingBurstTime[i] = processes[i].burst_time;

    while (true) {
        bool done = true;
        for (int i = 0; i < n; ++i) {
            if (remainingBurstTime[i] > 0) {
                done = false;
                if (remainingBurstTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingBurstTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingBurstTime[i];
                    processes[i].completion_time = currentTime;
                    remainingBurstTime[i] = 0;
                }
            }
        }
        if (done)
            break;
    }

    for (int i = 0; i < n; ++i) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

bool comparePriority(Process& p1, Process& p2) {
    return p1.priority < p2.priority;
}

void preemptivePriority(vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completed = 0;
    vector<bool> completedProcesses(n, false);

    while (completed < n) {
        int highestPriority = INT_MAX;
        int chosenProcessIndex = -1;

        for (int i = 0; i < n; ++i) {
            if (!completedProcesses[i] && processes[i].arrival_time <= currentTime && processes[i].priority < highestPriority && processes[i].remaining_time > 0) {
                highestPriority = processes[i].priority;
                chosenProcessIndex = i;
            }
        }

        if (chosenProcessIndex != -1) {
            processes[chosenProcessIndex].remaining_time--;
            currentTime++;

            if (processes[chosenProcessIndex].remaining_time == 0) {
                processes[chosenProcessIndex].completion_time = currentTime;
                processes[chosenProcessIndex].turnaround_time = processes[chosenProcessIndex].completion_time - processes[chosenProcessIndex].arrival_time;
                processes[chosenProcessIndex].waiting_time = processes[chosenProcessIndex].turnaround_time - processes[chosenProcessIndex].burst_time;
                completedProcesses[chosenProcessIndex] = true;
                completed++;
            }
        } else {
            currentTime++;
        }
    }
}

void nonPreemptivePriority(vector<Process>& processes) {
    sort(processes.begin(), processes.end(), comparePriority);
    int currentTime = 0;
    for (auto& process : processes) {
        if (process.arrival_time > currentTime)
            currentTime = process.arrival_time;
        process.completion_time = currentTime + process.burst_time;
        currentTime = process.completion_time;
        process.turnaround_time = process.completion_time - process.arrival_time;
        process.waiting_time = process.turnaround_time - process.burst_time;
    }
}

void displayResult(const vector<Process>& processes) {
    double avgTurnaroundTime = 0, avgWaitingTime = 0;

    // Print header
    cout << "Process\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n";

    for (const Process& p : processes) {
        cout << p.id << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
             << p.priority << "\t\t" << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;

        avgTurnaroundTime += p.turnaround_time;
        avgWaitingTime += p.waiting_time;
    }
    avgTurnaroundTime /= processes.size();
    avgWaitingTime /= processes.size();

    // Print average
    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime << " units\n";
    cout << "Average Waiting Time: " << avgWaitingTime << " units\n";
}

void inputProcesses(vector<Process>& processes, bool requirePriority = false) {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; ++i) {
        int arrival, burst, priority = 0;
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> arrival;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> burst;
        if (requirePriority) {
            cout << "Process " << i + 1 << " Priority: ";
            cin >> priority;
        }
        processes.push_back(Process(i + 1, arrival, burst, priority));
    }
}

int main() {
    vector<Process> processes;
    int timeQuantum;

    // FCFS Scheduling
    inputProcesses(processes);
    fcfs(processes);
    cout << "\nFCFS Scheduling:\n";
    displayResult(processes);

    // SJF Non-Preemptive Scheduling
    // processes.clear();
    // inputProcesses(processes);
    sjfNP(processes);
    cout << "\nSJF Non-Preemptive Scheduling:\n";
    displayResult(processes);

    // SJF Preemptive Scheduling
    // processes.clear();
    // inputProcesses(processes);
    sjfPreemptive(processes);
    cout << "\nSJF Preemptive Scheduling:\n";
    displayResult(processes);

    // Round Robin Scheduling
    // processes.clear();
    // inputProcesses(processes);
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;
    roundRobin(processes, timeQuantum);
    cout << "\nRound Robin Scheduling:\n";
    displayResult(processes);

    // Priority Non-Preemptive Scheduling
    // processes.clear();
    // inputProcesses(processes, true);
    nonPreemptivePriority(processes);
    cout << "\nPriority Non-Preemptive Scheduling:\n";
    displayResult(processes);

    // Priority Preemptive Scheduling
    // processes.clear();
    // inputProcesses(processes, true);
    preemptivePriority(processes);
    cout << "\nPriority Preemptive Scheduling:\n";
    displayResult(processes);

    //Sample Input
//4
//0 2
//1 2
//5 3
//6 4
    return 0;
}
