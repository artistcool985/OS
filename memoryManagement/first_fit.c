#include <stdio.h>
#include <stdlib.h>
#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processRequirements[MAX_PROCESSES];
int availableMemory[MAX_SLOTS];
int isFinished[MAX_PROCESSES];

void initialize()
{
    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement of process %d\n", i);
        scanf("%d", &processRequirements[i]);
    }
    printf("\n\n");
    for(int i = 0; i < MAX_SLOTS; i++)
    {
        printf("Enter the available memory in slot %d\n", i);
        scanf("%d", &availableMemory[i]);
    }
    
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        isFinished[i] = 0;
    }
}

void firstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
        if (isFinished[i] == 0)
            for (int j = 0; j < MAX_SLOTS; j++)
                if (processRequirements[i] < availableMemory[j])
                {
                    printf("Process %d assigned to slot %d\n", i, j);
                    isFinished[i] = 1;
                    availableMemory[j] = availableMemory[j] - processRequirements[i];
                    break;
                }
    for(int i = 0; i < MAX_PROCESSES; i++)
        if(isFinished[i] == 0)
            printf("Memory can't be allocated for process %d\n", i);
}

int main()
{
    initialize();
    firstFit();
}
