#include <stdio.h>
#include <stdlib.h>

#define MAX_SPROCKETS 10

/*
 * Algorithm:
 *  -Put ratios into sorted linked list
 *  -Calculate max of all spreads with sorted list
 */

struct node {
    double value;
    struct node* next;
};

void insert(struct node* n, double value) {
    if (n->value == 0) {
        n->value = value;
        return;
    }

    if (value < n->value) {
        struct node* next = malloc(sizeof(struct node));
        next->next = NULL;
        next->value = n->value;
        n->next = next;
        n->value = value;
        return;
    }

    while (n->next != NULL && n->next->value < value) {
        n = n->next;
    }

    struct node* next = malloc(sizeof(struct node));
    next->next = n->next;
    next->value = value;
    n->next = next;
}

int main(int argc, char* args[]) {
    struct node* ratios = malloc(sizeof(struct node));
    ratios->value = 0;

    int front[MAX_SPROCKETS];
    int rear[MAX_SPROCKETS];
    int frontc, rearc;

    while (scanf("%d%d", &frontc, &rearc) == 2) {
        for (int f = 0; f < frontc; f++) {
            scanf("%d", front+f);
        }
        for (int r = 0; r < rearc; r++) {
            scanf("%d", rear+r);
        }

        for (int r = 0; r < rearc; r++) {
            for (int f = 0; f < frontc; f++) {
                double ratio = (double) rear[r] / front[f];
                insert(ratios, ratio);
            }
        }

        struct node* n = ratios;
        double max_spread = n->value;
        while (n->next != NULL) {
            double spread = n->next->value / n->value;
            if (spread > max_spread) {
                max_spread = spread;
            }
            struct node* next = n->next;
            free(n);
            n = next;
        }

        printf("%.2f\n", max_spread);
    }

    return EXIT_SUCCESS;
}
