#include <stdio.h>
#include <stdlib.h>

struct interval {
    int index;
    double start;
    double end;
};

int compare(const void* v1, const void* v2) {
    return ((struct interval*)v1)->start <
           ((struct interval*)v2)->start ? -1 : 1;
}

int main() {
    double start, end;
    struct interval ints[20000];
    int used[20000];

    while (scanf("%lf %lf", &start, &end) == 2) {
        int intc;
        scanf("%d", &intc);

        for (int i = 0; i < intc; i++) {
            ints[i].index = i;
            scanf("%lf %lf", &ints[i].start, &ints[i].end);
        }

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
