#include <stdio.h>
#include <stdlib.h>

#define MAX_SPROCKETS 10

/*
 * Algorithm:
 *  -Put ratios into sorted linked list
 *  -Calculate max of all spreads with sorted list
 */

void insert(double array[], int length, double value) {
    int start = 0;
    int end = length;

    while (start < end) {
        int middle = (start + end) >> 1;
        double current = array[middle];

        if (current < value) {
            start = middle + 1;
        } else if (value < current) {
            end = middle;
        }
    }

    for (int i = length; i > start; i--) {
        array[i] = array[i-1];
    }
    array[start] = value;
}

int main(int argc, char* args[]) {
    int front[MAX_SPROCKETS];
    int rear[MAX_SPROCKETS];
    double ratios[MAX_SPROCKETS*MAX_SPROCKETS];
    int frontc, rearc, ratioc;

    while (scanf("%d%d", &frontc, &rearc) == 2) {
        ratioc = 0;

        for (int f = 0; f < frontc; f++) {
            scanf("%d", front+f);
        }
        for (int r = 0; r < rearc; r++) {
            scanf("%d", rear+r);
        }

        for (int r = 0; r < rearc; r++) {
            for (int f = 0; f < frontc; f++) {
                double ratio = (double) rear[r] / front[f];
                insert(ratios, ratioc++, ratio);
            }
        }

        double max_spread = 0;
        for (int i = 0; i < ratioc-1; i++) {
            double spread = ratios[i+1] / ratios[i];
            if (spread > max_spread) {
                max_spread = spread;
            }
        }

        printf("%.2f\n", max_spread);
    }

    return EXIT_SUCCESS;
}
