#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int id;
    int burstTime;
    int arrivalTime;
    int remainingTime;
    bool completed;
    int completionTime;
};

void SRTF(struct Node* processes, int n) {
    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        int shortestRemainingTime = __INT_MAX__;
        int shortestIndex = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime &&
                processes[i].remainingTime < shortestRemainingTime) {
                shortestRemainingTime = processes[i].remainingTime;
                shortestIndex = i;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        // Execute the shortest process for one unit of time
        processes[shortestIndex].remainingTime--;
        currentTime++;

        // Check if the process is completed
        if (processes[shortestIndex].remainingTime == 0) {
            processes[shortestIndex].completed = true;
            completedProcesses++;
            processes[shortestIndex].completionTime = currentTime;

            int waitingTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime - processes[shortestIndex].burstTime;
            printf("Process %d completed. Arrival Time: %d, Burst Time: %d, Waiting Time: %d\n",
                   processes[shortestIndex].id, processes[shortestIndex].arrivalTime,
                   processes[shortestIndex].burstTime, waitingTime);
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Node* processes = malloc(n * sizeof(struct Node));

    printf("Enter the process details:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Enter Arrival Time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter Burst Time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].id = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].completed = false;
    }

    printf("Order of Execution:\n");
    printf("Process ID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrivalTime, processes[i].burstTime);
    }

    SRTF(processes, n);

    // Calculate and print turnaround time
    printf("Turnaround Time:\n");
    printf("Process ID\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        int turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        printf("%d\t\t%d\n", processes[i].id, turnaroundTime);
    }

    free(processes);

    return 0;
}
