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
    return ((struct interval*)v1)->end >
           ((struct interval*)v2)->end ? -1 : 1;
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
        //printf("[%.2f, %.2f]\n", start, end);
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%lf %lf", &ints[i].start, &ints[i].end);
        }

        //print_intervals(ints, intc);
        
        int usedn = 0;

        if (start == end) {
            struct interval *valid = NULL;
            for (int i = 0; i < intc; i++) {
                if (ints[i].start <= start && end <= ints[i].end) {
                    valid = &ints[i];
                    break;
                }
            }
            if (valid) {
                used[0] = valid->index;
                usedn = 1;
            }
        } else {
            /* sort intervals by size of intersection with main interval */
            qsort(ints, intc, sizeof(struct interval), compare);
        }

        int pindex = -1;
        double pstart = end;
        for (int i = 0; start < end && i < intc; i++) {
            if (ints[i].end < end) {
                if (pindex == -1) {
                    break;
                } else {
                    /* use interval */
                    used[usedn++] = pindex;
                    /* move forward */
                    end = pstart;
                    pindex = -1;
                    /* reevaluate current interval with moved now */
                    i--;
                }
            } else {
                /* set to potential if contributing more */
                if (ints[i].start <= pstart) {
                    pindex = ints[i].index;
                    pstart = ints[i].start;
                }
            }
        }
        if (pindex != -1) {
            used[usedn++] = pindex;
            end = pstart;
        }

        if (start >= end && usedn > 0) {
            printf("%d\n", usedn);
            for (int i = 0; i < usedn; i++) {
                printf("%d ", used[i]);
            }
            printf("\n");
        } else {
            printf("impossible\n");
        }
    }

    return EXIT_SUCCESS;
}
