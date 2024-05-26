#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int burstTime;
    int completionTime; // New field to store completion time
};

void FCFS(struct Node* arr, int n)
{
    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\n", arr[i].id, arr[i].burstTime);
    }

    int completionTime = 0; // Initialize completion time
    int totalWaitingTime = 0; // Initialize total waiting time

    for (int i = 0; i < n; i++)
    {
        completionTime += arr[i].burstTime; // Update completion time
        arr[i].completionTime = completionTime; // Store completion time for the process

        // Calculate waiting time for each process
        int waitingTime = completionTime - arr[i].burstTime;
        totalWaitingTime += waitingTime;
    }

    printf("Turnaround Time:\n");
    printf("Process ID\tTurnaround Time\n");

    // Print turnaround time for each process
    for (int i = 0; i < n; i++)
    {
        int turnaroundTime = arr[i].completionTime; // Turnaround time is equal to completion time
        printf("%d\t\t%d\n", arr[i].id, turnaroundTime);
    }

    // Calculate and print average waiting time
    float avgWaitingTime = (float)totalWaitingTime / n;
    printf("Average waiting time: %.2f\n", avgWaitingTime);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Node* processes = (struct Node*)malloc(n * sizeof(struct Node));

    printf("Enter the process IDs and burst times:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &processes[i].id);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burstTime);
    }

    FCFS(processes, n);

    free(processes);

    return 0;
}
