#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void cScan(int* array, int head, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }

    int index = 0;

    for (int i = 0; i < size; i++)
    {
        if (array[i] < head)
        {
            index = i;
        }
    }

    printf("Head moves from %d to 199\n", head);
    printf("Head moves from 199 to 0\n");
    printf("Head moves from 0 to %d\n", array[index]);

    int headMovement = (199 - head) + (199 - 0) + (array[index] - 0);

    printf("Total head movements: %d\n", headMovement);
}

int main()
{
    int size;
    printf("Enter the number of elements in the sequence: ");
    scanf("%d", &size);

    int* sequence = (int*)malloc(size * sizeof(int));
    printf("Enter the sequence: ");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &sequence[i]);
    }

    int head;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    cScan(sequence, head, size);

    free(sequence);

    return 0;
}
