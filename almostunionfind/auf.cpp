/*
 * Algorithm:
 * -array of pointers to sets. nums[i-1] points to set which contains i
 * -array of sets of numbers
 */
#include <iostream>
#include <set>
#include <numeric>

using namespace std;

void set_debug(set<int> *sets, set<int> **nums, int numc) {
    printf("Sets:\n");
    for (int i = 0; i < numc; i++) {
        printf("%d: ( ", i+1);
        for (auto n : *nums[i]) {
            printf("%d ", n);
        }
        printf(")\n");
    }
}

void set_union(set<int> *sets, set<int> **nums, int p, int q) {
    set<int> *src = rums[p-1];
    set<int> *dst = nums[q-1];

    if (dst->size() < src->size()) {
        src = nums[q-1];
        dst = nums[p-1];
    }

    if (src != dst) {
        dst->insert(src->begin(), src->end());

        for (auto n : *src) {
            nums[n-1] = dst;
        }
    }
}

void set_move(set<int> *sets, set<int> **nums, int p, int q) {
    set<int> *src = nums[p-1];
    set<int> *dst = nums[q-1];

    if (src != dst) {
        dst->insert(p);
        src->erase(p);

        nums[p-1] = dst;
    }
}

void set_print(set<int> *sets, set<int> **nums, int p) {
    set<int> *target = nums[p-1];

    int sum = accumulate(target->begin(), target->end(), 0);
    printf("%lu %d\n", target->size(), sum);
}

int main() {
    int numc, commc;

    while (scanf("%d %d", &numc, &commc) == 2) {
        set<int> sets[numc];
        set<int> *nums[numc];

        for (int i = 0; i < numc; i++) {
            sets[i].insert(i+1);
            nums[i] = &sets[i];
        }

        for (int i = 0; i < commc; i++) {
            int command, p, q;
            scanf("%d", &command);
            
            switch (command) {
            case 1:
                scanf("%d%d", &p, &q);
                set_union(sets, nums, p, q);
                break;
            case 2:
                scanf("%d%d", &p, &q);
                set_move(sets, nums, p, q);
                break;
            case 3:
                scanf("%d", &p);
                set_print(sets, nums, p);
            }
        }
    }
}
