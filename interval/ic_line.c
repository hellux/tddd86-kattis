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
        printf("%d: [%.2lf,%.2lf]\n", ints[i].index, ints[i].start,
                                      ints[i].end);
    }
}

int main() {
    double start, end;
    struct interval ints[20000];
    int used[20000];

    while (scanf("%lf %lf", &start, &end) == 2) {
        printf("[%.2f, %.2f]\n", start, end);
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%lf %lf", &ints[i].start, &ints[i].end);
        }

        print_intervals(ints, intc);

        /* sort intervals by size of intersection with main interval */
        qsort(ints, intc, sizeof(struct interval), compare);
        
        int usedn = 0;

        int pindex = -1;
        double pend = start;
        for (int i = 0; start < end && i < intc; i++) {
            if (ints[i].start > start) {
                if (pindex == -1) {
                    break;
                } else {
                    /* use interval */
                    used[usedn++] = pindex;
                    /* move forward */
                    start = pend;
                    pindex = -1;
                    /* reevaluate current interval with moved now */
                    i--;
                }
            } else {
                /* set to potential if contributing more */
                if (ints[i].end >= pend) {
                    pindex = ints[i].index;
                    pend = ints[i].end;
                }
            }
        }
        if (pindex != -1) {
            used[usedn++] = pindex;
            start = pend;
        }

        if (start >= end) {
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
