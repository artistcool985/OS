#include <stdio.h>
#include <stdlib.h>

#define MAX 200

int calculateAbsoluteDifference(int a, int b) {
    return abs(a - b);
}

int findClosestRequest(int* requests, int head, int size, int visited[]) {
    int minDifference = MAX;
    int minIndex = -1;

    for (int i = 0; i < size; i++) {
        if (!visited[i]) {
            int difference = calculateAbsoluteDifference(head, requests[i]);
            if (difference < minDifference) {
                minDifference = difference;
                minIndex = i;
            }
        }
    }

    return minIndex;
}

void sstfDisk(int* requests, int initialHead, int size) {
    int headMovement = 0;
    int visited[MAX] = {0};

    for (int i = 0; i < size; i++) {
        int closestIndex = findClosestRequest(requests, initialHead, size, visited);
        visited[closestIndex] = 1;
        printf("Head moved from %d to %d\n", initialHead, requests[closestIndex]);
        headMovement += calculateAbsoluteDifference(initialHead, requests[closestIndex]);
        initialHead = requests[closestIndex];
    }

    printf("Total head movements: %d\n", headMovement);
}

int main() {
    int requestSequence[MAX];
    int initialHead;
    int size;

    printf("Enter the number of requests: ");
    scanf("%d", &size);

    printf("Enter the sequence of requests: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &requestSequence[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    sstfDisk(requestSequence, initialHead, size);

    return 0;
}
