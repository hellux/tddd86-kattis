#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_CDS 1000000

/*
 * Return pos of value in sorted array (if in array, otherwise where it would be)
 */
unsigned pos(unsigned array[], unsigned start, unsigned end, unsigned value, bool* found) {
    while (start < end) {
        unsigned middle = (start + end) >> 1;
        unsigned current = array[middle];

        if (current < value) {
            start = middle + 1;
        } else if (value < current) {
            end = middle;
        } else {
            *found = true;
            return middle;
        }
    }

    return start;
}

int main(int argc, char* args[]) {
    unsigned jack_catalog[MAX_CDS];
    unsigned jack, jill;
    char buffer[10000];
    unsigned buffer_size = 0;

    while(scanf("%u%u", &jack, &jill) == 2) {
        if (jack == 0 && jill == 0) break;

        unsigned size;
        for (size = 0; size < jack; size++) {
            scanf("%u", jack_catalog+size);
        }

        unsigned start = 0;
        unsigned sell = 0;
        for (unsigned i = 0; i < jill; i++) {
            unsigned cat_num;
            scanf("%u", &cat_num);

            bool found = false;
            start = pos(jack_catalog, start, size, cat_num, &found);
            if (found) {
                sell++;
            }
        }
        
        sprintf(buffer+buffer_size, "%u", sell);
        buffer_size += strlen(buffer+buffer_size)+1;
        buffer[buffer_size-1] = '\n';
    }
    
    buffer[buffer_size] = '\0';
    printf(buffer);

    return EXIT_SUCCESS;
}
