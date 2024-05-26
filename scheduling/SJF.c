#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int burstTime;
};

void SJF(struct Node* arr, int n)
{
    // Sorting processes based on burst time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j].burstTime > arr[j + 1].burstTime)
            {
                // Swap burst times
                int temp = arr[j].burstTime;
                arr[j].burstTime = arr[j + 1].burstTime;
                arr[j + 1].burstTime = temp;

                // Swap process IDs
                temp = arr[j].id;
                arr[j].id = arr[j + 1].id;
                arr[j + 1].id = temp;
            }
        }
    }

    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\tTurnaround Time\n");

    int turnaroundTime = 0;
    int totalWaitingTime = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\n", arr[i].id, arr[i].burstTime, turnaroundTime);
        totalWaitingTime += turnaroundTime;
        turnaroundTime += arr[i].burstTime;
    }

    printf("Average turnaround time: %.2f\n", (float)totalWaitingTime / n);
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Node* processes = (struct Node*)malloc(n * sizeof(struct Node));

    printf("Enter the burst time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].id = i + 1;
    }

    SJF(processes, n);

    free(processes);

    return 0;
}
