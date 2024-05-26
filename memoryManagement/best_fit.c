#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processSizes[MAX_PROCESSES];
int slotSizes[MAX_SLOTS];
int processFinished[MAX_PROCESSES];

void initialize()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement of process %d: ", i);
        scanf("%d", &processSizes[i]);
    }

    for (int i = 0; i < MAX_SLOTS; i++)
    {
        printf("Enter the available memory in slot %d: ", i);
        scanf("%d", &slotSizes[i]);
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        processFinished[i] = 0;
    }
}

int findBestSlot(int processSize)
{
    int bestSlot = -1;
    int minSize = INT_MAX;

    for (int j = 0; j < MAX_SLOTS; j++)
    {
        if (slotSizes[j] >= processSize && slotSizes[j] < minSize)
        {
            minSize = slotSizes[j];
            bestSlot = j;
        }
    }

    return bestSlot;
}

void allocateMemory()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (processFinished[i] == 0)
        {
            int bestSlot = findBestSlot(processSizes[i]);

            if (bestSlot != -1)
            {
                printf("Process %d assigned to slot %d\n", i, bestSlot);
                processFinished[i] = 1;
                slotSizes[bestSlot] -= processSizes[i];
            }
            else
            {
                printf("Memory can't be allocated for process %d\n", i);
            }
        }
    }
}

int main()
{
    initialize();
    allocateMemory();

    return 0;
}
