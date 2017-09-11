#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_TERMS 1000

void insert(int array[], int length, int value) {
    int start = 0;
    int end = length;
    while (start < end) {
        int middle = (start + end) / 2;
        int current = array[middle];

        if (current < value) {
            start = middle + 1;
        } else if (value < current) {
            end = middle;
        } else {
            return;
        }
    }
    
    for (int i = length; i > start; i--) {
        array[i] = array[i-1];
    }
    array[start] = value;
}

int min(int n1, int n2) {
    if (n1 < n2) {
        return n1;
    } else {
        return n2;
    }
}

int closest_sum(int array[], int end, int value) {
    int start = 0;
    int min_diff = INT_MAX;

    while (start < end - 1) {
        int sum = array[start] + array[end-1];

        if (value < sum) {
            end--;
        } else {
            start++;
        }

        if (abs(sum-value) < abs(min_diff)) {
            min_diff = sum-value;
        }
    }

    return value + min_diff;
}

int main() {
    int terms[MAX_TERMS];
    int termc, queryc;

    int casec = 0;
    while (scanf("%d", &termc) == 1) {
        printf("Case %d:\n", ++casec);
        for (int t = 0; t < termc; t++) {
            int term;
            scanf("%d", &term);
            insert(terms, t, term);
        }

        scanf("%d", &queryc);
        for (int q = 0; q < queryc; q++) {
            int query;
            scanf("%d", &query);
            int close = closest_sum(terms, termc, query);
            printf("Closest sum to %d is %d.\n", query, close);
        }
    }
}
