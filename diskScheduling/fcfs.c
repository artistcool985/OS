#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void fcfsDiskScheduling(int* requests, int head, int size)
{
    int current = head;
    int headMovement = 0;

    for (int i = 0; i < size; i++)
    {
        printf("Head moved from %d to %d\n", current, requests[i]);
        headMovement = headMovement + abs(current - requests[i]);
        current = requests[i];
    }

    printf("Total head movements: %d\n", headMovement);
}

int main()
{
    int sequence[MAX];
    int head, size;

    printf("Enter the number of disk requests: ");
    scanf("%d", &size);

    printf("Enter the disk sequence: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &sequence[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    fcfsDiskScheduling(sequence, head, size);

    return 0;
}
