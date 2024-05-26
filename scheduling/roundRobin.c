#include <stdio.h>
#include <stdbool.h>
struct Process {
int id;
int burstTime;
int remainingTime;
int arrivalTime;
bool completed;
};
void roundRobin(struct Process* processes, int n, int quantum) {
int currentTime = 0;
int completedProcesses = 0;
while (completedProcesses < n) {
for (int i = 0; i < n; i++) {
if (!processes[i].completed && processes[i].arrivalTime <= currentTime &&
processes[i].remainingTime > 0) {
// Execute the process for the quantum time or for its remaining time, whichever is smaller
int executeTime = (processes[i].remainingTime < quantum) ? processes[i].remainingTime : quantum;
processes[i].remainingTime -= executeTime;
currentTime += executeTime;
if (processes[i].remainingTime == 0) {
processes[i].completed = true;
completedProcesses++;
int waitingTime = currentTime - processes[i].burstTime - processes[i].arrivalTime;
printf("Process %d completed. Burst Time: %d, Waiting Time: %d\n",
processes[i].id, processes[i].burstTime, waitingTime);
}
}
}
}
}
void sortProcessesByArrivalTime(struct Process* processes, int n) {
// Simple bubble sort to sort processes based on arrival time
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
// Swap
struct Process temp = processes[j];
processes[j] = processes[j + 1];
processes[j + 1] = temp;
}
}
}
}
int main() {
struct Process processes[] = {
{1, 6, 6, 0, false},
{2, 8, 8, 2, false},
{3, 7, 7, 3, false},
{4, 3, 3, 7, false}
};
int n = sizeof(processes) / sizeof(processes[0]);
int quantum = 2; // Change the quantum value as needed
printf("Order of Execution:\n");
printf("Process ID\tArrival Time\tBurst Time\n");
for (int i = 0; i < n; i++) {
printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime);
}
// Sort processes based on arrival time before executing
sortProcessesByArrivalTime(processes, n);
roundRobin(processes, n, quantum);
return 0;
}