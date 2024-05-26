//ALL_Fit
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROCESSES 4
#define MAX_SLOTS 5

int processSizes[MAX_PROCESSES];
int slotSizes[MAX_SLOTS];
int processFinished[MAX_PROCESSES];

int isFinished[MAX_PROCESSES];
int processRequirements[MAX_PROCESSES];
int availableMemory[MAX_SLOTS];

int processCompletion[MAX_PROCESSES];

int isProcessFinished[MAX_PROCESSES];

//Sample inputs
//First line-> 20 30 40 50
//Second line-> 30 20 100 50 60
void initialize_bestfit()
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

void initialize_firstfit()
{
    for(int i = 0; i < MAX_PROCESSES; i++)
    {
        printf("Enter the memory requirement of process %d: ", i);
        scanf("%d", &processRequirements[i]);
    }
    printf("\n\n");
    for(int i = 0; i < MAX_SLOTS; i++)
    {
        printf("Enter the available memory in slot %d: ", i);
        scanf("%d", &availableMemory[i]);
    }
    
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        isFinished[i] = 0;
    }
}

void initialize_nextfit()
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

void initialize_worstfit()
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

void bestfit()
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

void firstFit()
{
    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (isFinished[i] == 0)
        {
            for (int j = 0; j < MAX_SLOTS; j++)
            {
                if (processRequirements[i] <= availableMemory[j])
                {
                    printf("Process %d assigned to slot %d\n", i, j);
                    isFinished[i] = 1;
                    availableMemory[j] -= processRequirements[i];
                    break;
                }
            }
        }
    }

    for (int i = 0; i < MAX_PROCESSES; i++)
    {
        if (isFinished[i] == 0)
        {
            printf("Memory can't be allocated for process %d\n", i);
        }
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

        printf("\nMemory Allocation Menu:\n");
        printf("1. Best Fit\n");
        printf("2. First Fit\n");
        printf("3. Next Fit\n");
        printf("4. Worst Fit\n");
        initialize_bestfit();
        bestfit();

    return 0;
}
