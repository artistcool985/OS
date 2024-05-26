#include <stdio.h>
#include <stdlib.h>

struct SegmentEntry {
    int base;
    int limit;
};

struct SegmentEntry segment_table[] = {
    {0, 4095},
    {8192, 16383}
};

void address_translation(int segment_num, int offset) {
    int base = segment_table[segment_num].base;
    int limit = segment_table[segment_num].limit;

    if (offset < limit) {
        int physical_address = base + offset;
        printf("Logical address: Segment %d, Offset %d ==> Physical address: %d\n", segment_num, offset, physical_address);
    } else {
        printf("Error: Offset exceeds segment limit\n");
    }
}

int main() {
    int logical_addresses[][2] = {
        
        {0, 100},
        {1, 5000},
        {0, 5000},
        {1, 10000}
    };

    for (int i = 0; i < sizeof(logical_addresses) / sizeof(logical_addresses[0]); i++) {
        int segment_num = logical_addresses[i][0];
        int offset = logical_addresses[i][1];
        address_translation(segment_num, offset);
    }

    return 0;
}
