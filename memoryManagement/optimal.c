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

int findOptimalPage(int pages[], int num_pages, int frames[], int num_frames, int current_index) {
    int farthest_index = -1;
    int farthest_distance = -1;

    for (int i = 0; i < num_frames; i++) {
        int page = frames[i];
        int future_index = -1;

        for (int j = current_index; j < num_pages; j++) {
            if (pages[j] == page) {
                future_index = j;
                break;
            }
        }

        if (future_index == -1) {
            return i;
        }

        if (future_index > farthest_distance) {
            farthest_distance = future_index;
            farthest_index = i;
        }
    }

    return farthest_index;
}

void optimalPageReplacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES];
    int page_faults = 0;

    initializeFrames(frames, MAX_FRAMES);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        printf("%d\t", current_page);

        if (!isPagePresent(frames, MAX_FRAMES, current_page)) {
            int replace_index = findOptimalPage(pages, num_pages, frames, MAX_FRAMES, i);
            frames[replace_index] = current_page;
            page_faults++;
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

    optimalPageReplacement(pages, num_pages);

    return 0;
}
