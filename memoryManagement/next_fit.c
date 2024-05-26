#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processRequirements[MAX_PROCESSES];
int availableMemory[MAX_SLOTS];
int processCompletion[MAX_PROCESSES];

void initialize()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement of process %d: ", i);
        scanf("%d", &processRequirements[i]);
    }

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        printf("Enter the available memory in slot %d: ", i);
        scanf("%d", &availableMemory[i]);
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        processCompletion[i] = 0;
    }
}

void nextFit()
{
    int currentSlot = 0; // Start from the first slot
    int completed = 0;

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processCompletion[i] == 0)
        {
            while (currentSlot < MAX_SLOTS && completed < MAX_SLOTS)
            {
                if (processRequirements[i] <= availableMemory[currentSlot])
                {
                    printf("Process %d assigned to slot %d\n", i, currentSlot);
                    processCompletion[i] = 1;
                    availableMemory[currentSlot] -= processRequirements[i];
                    break;
                }

                currentSlot = (currentSlot + 1) % MAX_SLOTS; // Move to the next slot
                completed++;
            }
        }
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processCompletion[i] == 0)
        {
            printf("Memory can't be allocated for process %d\n", i);
        }
    }
}

int main()
{
    initialize();
    nextFit();

    return 0;
}
