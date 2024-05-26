#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_SIZE 4096
#define PAGE_TABLE_SIZE 256
#define NUM_FRAMES 128

struct PageTableEntry {
    int frameNumber;
};

struct PageTableEntry pageTable[PAGE_TABLE_SIZE];

void initializePageTable() {
    srand(time(NULL));

    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        pageTable[i].frameNumber = rand() % NUM_FRAMES;
    }
}

void translateAddress(int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    int frameNumber = pageTable[pageNumber].frameNumber;
    int physicalAddress = frameNumber * PAGE_SIZE + offset;

    printf("Virtual address: %d ==> Physical address: %d\n", virtualAddress, physicalAddress);
}

int main() {
    initializePageTable();

    int numAddresses;
    printf("Enter the number of virtual addresses: ");
    scanf("%d", &numAddresses);

    int virtualAddresses[numAddresses];
    printf("Enter the virtual addresses:\n");
    for (int i = 0; i < numAddresses; i++) {
        scanf("%d", &virtualAddresses[i]);
    }

    for (int i = 0; i < numAddresses; i++) {
        translateAddress(virtualAddresses[i]);
    }

    return 0;
}
