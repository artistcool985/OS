#include <stdio.h>
#include <stdlib.h>

#define MAX 200

void diskSCAN(int* array, int initialHead, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    printf("Head moves from %d to 0\n", initialHead);
    printf("Head moves from 0 to %d\n", array[size - 1]);

    int headMovement = 0;

    int left = abs(initialHead - 0);
    int right = abs(array[size - 1] - 0);

    headMovement = left + right;

    printf("Total head movements: %d\n", headMovement);
}

int main()
{
    int size;
    printf("Enter the number of elements in the sequence: ");
    scanf("%d", &size);

    int sequence[MAX];
    printf("Enter the sequence of numbers:\n");
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &sequence[i]);
    }

    int initialHead;
    printf("Enter the initial head position: ");
    scanf("%d", &initialHead);

    diskSCAN(sequence, initialHead, size);

    return 0;
}
