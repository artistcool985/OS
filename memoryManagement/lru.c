#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3

void initializeFrames(int frames[], int size) {
    for (int i = 0; i < size; i++) {
        frames[i] = -1;
    }
}

bool isPagePresent(int frames[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int findLeastRecentlyUsedPage(int frames[], int num_frames, int access_time[]) {
    int lru_index = 0;
    int lru_time = access_time[0];

    for (int i = 1; i < num_frames; i++) {
        if (access_time[i] < lru_time) {
            lru_index = i;
            lru_time = access_time[i];
        }
    }

    return lru_index;
}

void lruPageReplacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES];
    int access_time[MAX_FRAMES];
    int page_faults = 0;

    initializeFrames(frames, MAX_FRAMES);
    for (int i = 0; i < MAX_FRAMES; i++) {
        access_time[i] = -1;
    }

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int currentPage = pages[i];
        printf("%d\t", currentPage);

        if (!isPagePresent(frames, MAX_FRAMES, currentPage)) {
            int lru_index = findLeastRecentlyUsedPage(frames, MAX_FRAMES, access_time);
            frames[lru_index] = currentPage;
            access_time[lru_index] = i; // Update access time
            page_faults++;
        } else {
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == currentPage) {
                    access_time[j] = i;
                    break;
                }
            }
        }

        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {

    int pages[] = {5, 3, 4, 2, 3, 3, 4, 4, 2, 3, 5, 7, 2};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    lruPageReplacement(pages, num_pages);

    return 0;
}
