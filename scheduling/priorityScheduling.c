#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int id;
    int time;
    int priority;
};

void swap(struct Node* p, struct Node* q)
{
    struct Node temp = *p;
    *p = *q;
    *q = temp;
}

void priorityScheduling(struct Node* arr, int n)
{
    int turnaroundTime = 0;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (arr[j].priority > arr[j+1].priority)
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }

    printf("Order of Execution:\n");
    printf("Process ID\tBurst Time\tPriority\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        turnaroundTime += arr[i].time;
        printf("%d\t\t%d\t\t%d\t\t%d\n", arr[i].id, arr[i].time, arr[i].priority, turnaroundTime);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Node* processes = (struct Node*)malloc(n * sizeof(struct Node));

    printf("Enter the process details (ID, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i+1);
        printf("ID: ");
        scanf("%d", &processes[i].id);
        printf("Burst Time: ");
        scanf("%d", &processes[i].time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
    }

    priorityScheduling(processes, n);

    free(processes);

    return 0;
}
