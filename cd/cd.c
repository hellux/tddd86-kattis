#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CDS 1000000

/*
 * Return pos of value in sorted array (if in array, otherwise where it would be)
 */
unsigned pos(unsigned array[], unsigned start, unsigned end, unsigned value) {
    while (start < end) {
        unsigned middle = (start + end) / 2;
        unsigned current = array[middle];

        if (current < value) {
            start = middle + 1;
        } else if (value < current) {
            end = middle;
        } else {
            return middle;
        }
    }
    return start;
}

int main(int argc, char* args[]) {
    unsigned jack_catalog[MAX_CDS];
    unsigned jack, jill;
    scanf("%u%u", &jack, &jill);
    
    unsigned start = 0;
    unsigned size;
    for (size = 0; size < jack; size++) {
        scanf("%u", jack_catalog+size);
    }

    unsigned sell = 0;
    for (int i = 0; i < jill; i++) {
        unsigned cat_num;
        scanf("%u", &cat_num);
        start = pos(jack_catalog, start, size, cat_num);
        if (jack_catalog[start] == cat_num) {
            sell++;
        }
    }

    printf("%u\n", sell);

    return EXIT_SUCCESS;
}
