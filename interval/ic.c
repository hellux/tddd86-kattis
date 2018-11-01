#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct interval {
    int index;
    float start;
    float end;
    float common;
};

float min(float a, float b) { return a < b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }

float common(float start1, float end1, float start2, float end2) {
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
    for (int i = 0; i < size; i++) {
        printf("%d: [%.2f,%.2f] %.2f\n", ints[i].index, ints[i].start,
                                         ints[i].end, ints[i].common);
    }
}

int main() {
    float start, end;
    struct interval ints[20000];

    while (scanf("%f %f", &start, &end) == 2) {
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%f %f", &ints[i].start, &ints[i].end);
            ints[i].common = common(ints[i].start, ints[i].end, start, end);
        }

        /* sort intervals by size of intersection with main interval */
        qsort(ints, intc, sizeof(struct interval), compare);

        //print_intervals(ints, intc);
        
        float size = end-start;
        int needed = 0;

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
            float new_size = end-start;
            if (new_size < size) {
                size = new_size;
                needed++;
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

            /* insertion sort intervals */
            for (int j = i+1; j < intc; j++) {
                k = j;
                while (k > i+1 && ints[k-1].common > ints[k].common) {
                    swap(ints+k-1, ints+k);
                    k--;
                }
            }
        }

        if (size <= 0) {
            printf("%d\n", needed);
            if (needed > 0) {
                for (int i = 0; i < needed; i++) {
                    printf("%d ", ints[i].index);
                }
                printf("\n");
            }
        } else {
            printf("impossible\n");
        }
    }

    return EXIT_SUCCESS;
}
