#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES] = {false};
int work[MAX_RESOURCES];

void initialize() {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }
}

bool canFinish(int pid) {
    int count = 0;
    for (int j = 0; j < MAX_RESOURCES; j++) {
        if (request[pid][j] <= work[j]) {
            count++;
        }
    }
    return count == MAX_RESOURCES;
}

bool deadlockDetection() {
    bool deadlock = true;

    while (deadlock) {
        deadlock = false;
        int completedProcesses = 0;

        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i] && canFinish(i)) {
                finish[i] = true;
                completedProcesses++;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    work[j] += allocation[i][j];
                }
                deadlock = true;
            }
        }

        if (completedProcesses == 0) {
            break;
        }
    }

    return deadlock;
}

int main() {
    initialize();
    bool isDeadlock = deadlockDetection();

    if (isDeadlock) {
        printf("Deadlock detected.\n");
    } else {
        printf("No deadlock detected.\n");
    }

    return 0;
}
