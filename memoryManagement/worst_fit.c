#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processSizes[MAX_PROCESSES];
int slotSizes[MAX_SLOTS];
int isProcessFinished[MAX_PROCESSES];

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
        isProcessFinished[i] = 0;
    }
}

void worstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (isProcessFinished[i] == 0)
        {
            int bestSlot = -1;
            int maxSize = INT_MIN;

            for (int j = 0; j < MAX_SLOTS; j++)
            {
                if (slotSizes[j] >= processSizes[i] && slotSizes[j] > maxSize)
                {
                    maxSize = slotSizes[j];
                    bestSlot = j;
                }
            }

            if (bestSlot != -1)
            {
                printf("Process %d assigned to slot %d\n", i, bestSlot);
                isProcessFinished[i] = 1;
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
    worstFit();

    return 0;
}
