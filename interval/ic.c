#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct interval {
    int index;
    double start;
    double end;
    double common;
};

double min(double a, double b) { return a < b ? a : b; }
double max(double a, double b) { return a > b ? a : b; }

double common(double start1, double end1, double start2, double end2) {
    return min(end1, end2) - max(start1, start2);
}

void swap(struct interval *a, struct interval *b) {
    struct interval tmp = *a;
    *a = *b;
    *b = tmp;
}

int compare(const void* v1, const void* v2) {
    return ((struct interval*)v1)->common <
           ((struct interval*)v2)->common;
}

void print_intervals(struct interval *ints, int size) {
    printf("intervals:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: [%.2lf,%.2lf] %.2lf\n", ints[i].index, ints[i].start,
                                      ints[i].end, ints[i].common);
    }
}

void print_intervals_comp(struct interval *ints, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: [%.2lf,%.2lf]\n", ints[i].index, ints[i].start,
                                      ints[i].end);
    }
}

int main() {
    double start, end;
    struct interval ints[20000];
    int used[20000];

    while (scanf("%lf %lf", &start, &end) == 2) {
        //printf("[%.2f, %.2f]\n", start, end);
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%lf %lf", &ints[i].start, &ints[i].end);
            ints[i].common = common(ints[i].start, ints[i].end, start, end);
        }
        
        print_intervals_comp(ints, intc);

        /* sort intervals by size of intersection with main interval */
        qsort(ints, intc, sizeof(struct interval), compare);

        double size = end-start;
        int usedn = 0;

        /* go through intervals, starting with largest */
        for (int i = 0; i < intc && size > 0; i++) {
            struct interval *valid = NULL;

            /* swap until interval overlaps edge */
            struct interval *curr = &ints[i];
            int k = i;
            for (int k = i; k < intc; k++) {
                if (curr->start <= start && curr->end >= start ||
                    curr->start <= end   && curr->end >= end) {
                    valid = curr;
                    break;
                } else {
                    swap(ints+i, ints+i+(++k));
                }
            }

            if (!valid) break;

            /* merge interval */
            if (valid->start <= start) start = valid->end;
            if (valid->end >= end) end = valid->start;

            /* check if interval changed */
            double new_size = end-start;
            if (new_size < size) {
                size = new_size;
                used[usedn++] = valid->index;
                /* exit if complete */
                if (new_size <= 0) {
                    break;
                }
            }

            /* recalculate intersection sizes */
            for (int j = i+1; j < intc; j++) {
                ints[j].common = common(ints[j].start, ints[j].end,
                                        start, end);
            }

            /* resort intervals */
            qsort(ints+i+1, intc-i-1, sizeof(struct interval), compare);
        }

        if (size <= 0) {
            printf("%d\n", usedn);
            /*
            if (usedn > 0) {
                for (int i = 0; i < usedn; i++) {
                    printf("%d ", used[i]);
                }
                printf("\n");
            }
            */
        } else {
            printf("impossible\n");
        }
    }

    return EXIT_SUCCESS;
}
