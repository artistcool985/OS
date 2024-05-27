//All Disk Scheduling Algorithm
#include <stdio.h>
#include <stdlib.h>

void FCFS(int arr[], int head, int n) {
    int total_head_movement = 0;
    int current_head = head;
    printf("FCFS Disk Scheduling:\n");
    printf("Track\tHead Movement\n");
    for (int i = 0; i < n; i++) {
        total_head_movement += abs(arr[i] - current_head);
        printf("%d\t%d\n", arr[i], abs(arr[i] - current_head));
        current_head = arr[i];
    }
    printf("Total Head Movement: %d\n", total_head_movement);
}

void SCAN(int arr[], int head, int n, int direction) {
    int total_head_movement = 0;
    int current_head = head;
    int seek_sequence[n + 2];
    int seek_count = 0;
    int size = 200;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int index;
    for (index = 0; index < n; index++) {
        if (arr[index] > head) break;
    }

    if (direction == 1) {
        for (int i = index; i < n; i++) {
            seek_sequence[seek_count++] = arr[i];
        }
        seek_sequence[seek_count++] = size - 1;
        for (int i = index - 1; i >= 0; i--) {
            seek_sequence[seek_count++] = arr[i];
        }
    } else {
        for (int i = index - 1; i >= 0; i--) {
            seek_sequence[seek_count++] = arr[i];
        }
        seek_sequence[seek_count++] = 0;
        for (int i = index; i < n; i++) {
            seek_sequence[seek_count++] = arr[i];
        }
    }

    printf("SCAN Disk Scheduling:\n");
    printf("Track\tHead Movement\n");
    for (int i = 0; i < seek_count; i++) {
        total_head_movement += abs(seek_sequence[i] - current_head);
        printf("%d\t%d\n", seek_sequence[i], abs(seek_sequence[i] - current_head));
        current_head = seek_sequence[i];
    }
    printf("Total Head Movement: %d\n", total_head_movement);
}

void SSTF(int arr[], int head, int n) {
    int total_head_movement = 0;
    int current_head = head;
    int seek_sequence[n];
    int seek_count = 0;
    int processed[n];
    for (int i = 0; i < n; i++) processed[i] = 0;

    printf("SSTF Disk Scheduling:\n");
    printf("Track\tHead Movement\n");
    while (seek_count < n) {
        int min = 1000, index = -1;
        for (int i = 0; i < n; i++) {
            if (!processed[i] && abs(arr[i] - current_head) < min) {
                min = abs(arr[i] - current_head);
                index = i;
            }
        }
        if (index != -1) {
            seek_sequence[seek_count++] = arr[index];
            total_head_movement += abs(arr[index] - current_head);
            printf("%d\t%d\n", arr[index], abs(arr[index] - current_head));
            current_head = arr[index];
            processed[index] = 1;
        }
    }
    printf("Total Head Movement: %d\n", total_head_movement);
}

void CSCAN(int arr[], int head, int n) {
    int total_head_movement = 0;
    int current_head = head;
    int seek_sequence[n + 2];
    int seek_count = 0;
    int size = 200;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    int index;
    for (index = 0; index < n; index++) {
        if (arr[index] > head) break;
    }

    for (int i = index; i < n; i++) {
        seek_sequence[seek_count++] = arr[i];
    }
    seek_sequence[seek_count++] = size - 1;
    seek_sequence[seek_count++] = 0;
    for (int i = 0; i < index; i++) {
        seek_sequence[seek_count++] = arr[i];
    }

    printf("CSCAN Disk Scheduling:\n");
    printf("Track\tHead Movement\n");
    for (int i = 0; i < seek_count; i++) {
        total_head_movement += abs(seek_sequence[i] - current_head);
        printf("%d\t%d\n", seek_sequence[i], abs(seek_sequence[i] - current_head));
        current_head = seek_sequence[i];
    }
    printf("Total Head Movement: %d\n", total_head_movement);
}

int main() {
    int arr[] = {82,170,43,140,24,16,190};
    int head = 50;
    int n = sizeof(arr) / sizeof(arr[0]);

    FCFS(arr, head, n);
    printf("\n");
    SSTF(arr, head, n);
    printf("\n");
    SCAN(arr, head, n, 1);
    printf("\n");
    CSCAN(arr, head, n);
    return 0;
}
