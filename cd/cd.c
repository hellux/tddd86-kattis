#include <stdlib.h>
#include <stdio.h>

#define MAX_CDS 1000000

/*
 * Return pos of value in sorted array (if in array, otherwise where it would be)
 */
unsigned long pos(unsigned long array[],
                  unsigned long start,
                  unsigned long end,
                  unsigned long value) {
    while (start < end) {
        unsigned long middle = (start + end) / 2;
        unsigned long current = array[middle];

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
    unsigned long jack_catalog[MAX_CDS];
    unsigned long jack, jill;
    scanf("%lu%lu", &jack, &jill);
    
    unsigned long start = 0;
    unsigned long size;
    for (size = 0; size < jack; size++) {
        scanf("%lu", jack_catalog+size);
    }

    unsigned long sell = 0;
    for (unsigned long i = 0; i < jill; i++) {
        unsigned long cat_num;
        scanf("%lu", &cat_num);
        start = pos(jack_catalog, start, size, cat_num);
        if (jack_catalog[start] == cat_num) {
            sell++;
        }
    }

    printf("%lu\n", sell);

    return EXIT_SUCCESS;
}
