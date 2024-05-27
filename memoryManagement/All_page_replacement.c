#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES_FIFO 3
#define MAX_FRAMES_LRU 4
#define MAX_FRAMES_OPT 4

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
    int frames[MAX_FRAMES_LRU];
    int access_time[MAX_FRAMES_LRU];
    int page_faults = 0;

    initializeFrames(frames,MAX_FRAMES_LRU);
    for (int i = 0; i < MAX_FRAMES_LRU; i++) {
        access_time[i] = -1;
    }

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int currentPage = pages[i];
        printf("%d\t", currentPage);

        if (!isPagePresent(frames, MAX_FRAMES_LRU, currentPage)) {
            int lru_index = findLeastRecentlyUsedPage(frames, MAX_FRAMES_LRU, access_time);
            frames[lru_index] = currentPage;
            access_time[lru_index] = i; // Update access time
            page_faults++;
        } else {
            for (int j = 0; j < MAX_FRAMES_LRU; j++) {
                if (frames[j] == currentPage) {
                    access_time[j] = i;
                    break;
                }
            }
        }

        for (int j = 0; j < MAX_FRAMES_LRU; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}



void initialize_frames_fifo(int frames[], int size) {
    for (int i = 0; i < size; i++) {
        frames[i] = -1;
    }
}

bool is_page_present(int frames[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

void fifo_page_replacement(int pages[], int num_pages) {
    int frames[MAX_FRAMES_FIFO];
    int frame_index = 0;
    int page_faults = 1;

    initialize_frames_fifo(frames, MAX_FRAMES_FIFO);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        printf("%d\t", current_page);

        if (!is_page_present(frames, MAX_FRAMES_FIFO, current_page)) {
            frames[frame_index] = current_page;
            frame_index = (frame_index + 1) % MAX_FRAMES_FIFO;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES_FIFO; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Page faults: %d\n", page_faults);
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
    int frames[MAX_FRAMES_OPT];
    int page_faults = 0;

    initializeFrames(frames, MAX_FRAMES_OPT);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        printf("%d\t", current_page);

        if (!isPagePresent(frames, MAX_FRAMES_OPT, current_page)) {
            int replace_index = findOptimalPage(pages, num_pages, frames, MAX_FRAMES_OPT, i);
            frames[replace_index] = current_page;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES_OPT; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}


int main() {

    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    lruPageReplacement(pages, num_pages);
    fifo_page_replacement(pages,num_pages);
    optimalPageReplacement(pages,num_pages);

    return 0;
}
