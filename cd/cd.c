#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_CDS 1000000

bool in_array(long array[], long length, long value) {
    long first = 0;
    long last = length - 1;
    while (first <= last) {
        long middle = (last + first) / 2;
        long current = array[middle];
        if (current < value) {
            first = middle + 1;
        } else if (value < current) {
            last = middle - 1;
        } else {
            return true;
        }
    }
    return false;
}

int main(int argc, char* args[]) {
    long jack_catalog[MAX_CDS];
    long jack, jill;
    scanf("%ld%ld", &jack, &jill);

    long count = 0;

    for (count = 0; count < jack; count++) {
        scanf("%ld", jack_catalog+count);
    }

    long sell = 0;
    for (int i = 0; i < jill; i++) {
        long cat_num;
        scanf("%ld", &cat_num);
        if (in_array(jack_catalog, count, cat_num)) {
            sell++;
        }
    }

    printf("%ld\n", sell);

    return EXIT_SUCCESS;
}
