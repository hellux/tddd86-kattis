#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct interval {
    int index;
    double start;
    double end;
};

double min(double a, double b) { return a < b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }

void swap(struct interval *a, struct interval *b) {
    struct interval tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_intervals(struct interval *ints, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: [%.2lf,%.2lf]\n", ints[i].index, ints[i].start,
                                      ints[i].end);
    }
}

int main() {
    double start, end;
    struct interval ints[20000];

    while (scanf("%lf %lf", &start, &end) == 2) {
        //printf("[%.2f, %.2f]\n", start, end);
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%lf %lf", &ints[i].start, &ints[i].end);
        }
        
        //print_intervals(ints, intc);

        /* sort intervals by size of intersection with main interval */
        int usedn = 0;

        /* min(end1, end2) - max(start1, start2);*/
        /* go through intervals, starting with largest */
        for (int i = 0; i < intc && start < end; i++) {
            /* select best interval */
            struct interval *best = NULL;
            double best_end = 0;
            for (int j = i; j < intc; j++) {
                if (ints[j].start <= start && start < ints[j].end) {
                    if (!best || ints[j].end > best_end) {
                        best = &ints[j];
                        best_end = ints[j].end;
                    }
                }
            }
            if (!best) break;

            start = best_end;
            swap(&ints[i], best);
            usedn++;
        }

        if (start >= end) {
            printf("%d\n", usedn);
            /*
            for (int i = 0; i < usedn; i++) {
                printf("%d ", ints[i].index);
            }
            printf("\n");
            */
        } else {
            printf("impossible\n");
        }
    }

    return EXIT_SUCCESS;
}
