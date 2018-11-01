#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct interval {
    int index;
    float start;
    float end;
};

float min(float a, float b) { return a < b ? a : b; }
float max(float a, float b) { return a > b ? a : b; }

void swap(struct interval *a, struct interval *b) {
    struct interval tmp = *a;
    *a = *b;
    *b = tmp;
}

int compare(const void* v1, const void* v2) {
    struct interval *i1 = (struct interval*)v1;
    struct interval *i2 = (struct interval*)v2;

    if (i1->start < i2->start) {
        return -1;
    } else if (i2->start < i1->start) {
        return 1;
    } else {
        return i1->end > i2->end ? -1 : 1;
    }
}

void print_intervals(struct interval *ints, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: [%.2f,%.2f]\n", ints[i].index, ints[i].start,
                                         ints[i].end);
    }
}

int main() {
    float start, end;
    struct interval ints[20000];
    int used[20000];

    while (scanf("%f %f", &start, &end) == 2) {
        //printf("[%.2f, %.2f]\n", start, end);
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            float istart, iend;
            scanf("%f %f", &istart, &iend);
            ints[i].start = max(start, istart);
            ints[i].end = max(min(end, iend), start);
        }

        /* sort intervals by size of intersection with main interval */
        qsort(ints, intc, sizeof(struct interval), compare);

        //print_intervals(ints, intc);
        
        int usedn = 0;

        float now = start;
        int pindex = -1;
        float pend = start;
        for (int i = 0; now < end && i < intc; i++) {
            if (ints[i].start > now) {
                if (pindex == -1) {
                    break;
                } else {
                    /* use interval */
                    used[usedn++] = pindex;
                    /* move forward */
                    now = pend;
                    pindex = -1;
                    /* reevaluate current interval with moved now */
                    i--;
                }
            } else {
                if (ints[i].end >= pend) {
                    pindex = ints[i].index;
                    pend = ints[i].end;
                }
            }
        }
        if (pindex != -1) {
            used[usedn++] = pindex;
            now = pend;
        }

        if (now >= end) {
            printf("%d\n", usedn);
            if (usedn > 0) {
                for (int i = 0; i < usedn; i++) {
                    printf("%d", used[i]);
                    if (i != usedn-1)
                        printf(" ");
                }
                printf("\n");
            }
        } else {
            printf("impossible\n");
        }
    }

    return EXIT_SUCCESS;
}
