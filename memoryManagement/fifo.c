#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3

void initialize_frames(int frames[], int size) {
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
    int frames[MAX_FRAMES];
    int frame_index = 0;
    int page_faults = 1;

    initialize_frames(frames, MAX_FRAMES);

    printf("Page\tFrames\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = pages[i];
        printf("%d\t", current_page);

        if (!is_page_present(frames, MAX_FRAMES, current_page)) {
            frames[frame_index] = current_page;
            frame_index = (frame_index + 1) % MAX_FRAMES;
            page_faults++;
        }

        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Page faults: %d\n", page_faults);
}

int main() {

    int pages[] = {0, 1, 4, 3, 0, 4, 2, 0, 1, 3, 4};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    fifo_page_replacement(pages, num_pages);

    return 0;
}
