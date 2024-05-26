#include <stdio.h>
int main()
{
    int n = 5, m = 3;
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 3}, {2, 1, 1}, {0, 0, 2}};
    int req[5][3] = {{0, 0, 0}, {2, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 0, 2}};
    int avail[3] = {0, 0, 0};
    int total_alloc[3] = {0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            total_alloc[j] += alloc[i][j];
        }
    }
    int total_available[3];
    for (int i = 0; i < m; i++)
    {
        total_available[i] = avail[i] + total_alloc[i];
    }
    printf("Total Available Resources: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", total_available[i]);
    }
    printf("\n");
    printf("Total Allocated Resources: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d ", total_alloc[i]);
    }
    printf("\n");
    int f[n], ans[n], ind = 0;
    for (int k = 0; k < n; k++)
    {
        f[k] = 0;
    }
    int deadlock = 0;
    for (int k = 0; k < 5; k++)
    {
        printf("Iteration %d\n", k + 1);
        printf("Available Resources: [%d,%d,%d]\n", avail[0], avail[1], avail[2]);
        int executed = 0;
        for (int i = 0; i < n; i++)
        {
            if (f[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (req[i][j] > avail[j])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    ans[ind++] = i;
                    printf("Process P%d can be executed\n", i);
                    for (int y = 0; y < m; y++)
                    {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                    executed = 1;
                    break;
                }
            }
        }
        if (!executed)
        {
            deadlock = 1;
            printf("\nDeadlock found. Processes involved: ");
            for (int i = 0; i < n; i++)
            {
                if (f[i] == 0)
                {
                    printf("P%d ", i);
                }
            }
            printf("\n");
            break;
        }
    }
    if (deadlock == 0)
    {
        printf("\nNo Deadlock is available\n");
    }
    return 0;
}
