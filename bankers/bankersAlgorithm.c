#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES] = {0};

void initialize() {
    // Input available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    // Input maximum demand of each process
    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input allocation of each process
    printf("Enter the allocation of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int safetyCheck() {
    int work[MAX_RESOURCES];
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    while (count < MAX_PROCESSES) {
        int found = 0;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocation[i][k];
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found)
            break;
    }

    if (count < MAX_PROCESSES) {
        printf("System is unsafe. Deadlock may occur.\n");
        return 0;
    } else {
        printf("System is safe. Safe sequence is: ");
        for (int i = 0; i < MAX_PROCESSES; i++)
            printf("%d ", safeSequence[i]);
        printf("\n");
        return 1;
    }
}

int requestResources(int pid, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[pid][i]) {
            printf("Process %d's request exceeds its maximum claim.\n", pid);
            return 0;
        }
        if (request[i] > available[i]) {
            printf("Process %d must wait since resources are not available.\n", pid);
            return 0;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (!safetyCheck()) {
        // Roll back changes if system is not safe
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        printf("Request cannot be granted.\n");
        return 0;
    }

    printf("Request granted.\n");
    return 1;
}

void displayCurrentState() {
    printf("\nCurrent state of the system:\n");

    printf("Available resources: ");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    printf("Max demand of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Allocation of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Need of each process:\n");
    for (int i = 0; i < MAX_PROCESSES; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < MAX_RESOURCES; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    initialize();

    displayCurrentState();

    safetyCheck();

    // Example: Process 0 requests resources
    int request[MAX_RESOURCES];
    printf("Enter the request for Process 0:\n");
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }
    requestResources(0, request);

    return 0;
}
