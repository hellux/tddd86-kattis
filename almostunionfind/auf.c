/*
 * Algorithm:
 * -array of pointers to set. index[i] points to set with i
 * -array of sets with list of numbers
 */
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

#define MAX_NUMS 100000
#define INIT_CAP 100

struct set {
    int* numbers;
    int size;
    int capacity;
};

struct set sets[MAX_NUMS];
struct set* set_ptrs[MAX_NUMS]; /* index = num-1 pointing to its set */
int numc;

void set_debug() {
#ifdef DEBUG
    printf("Sets:\n");
    for (int i = 0; i < numc; i++) {
        struct set* s = set_ptrs[i];
        printf("%d: %p ( ", i+1, s);
        for (int i = 0; i < s->size; i++) {
            printf("%d ", s->numbers[i]);
        }
        printf(") \n");
    }
#endif
}

void create_sets() {
    for (int i = 0; i < MAX_NUMS; i++) {
        struct set* s = &sets[i];
        s->capacity = INIT_CAP;
        s->numbers = malloc(sizeof(int)*s->capacity);
    }
}

void destroy_sets() {
    for (int i = 0; i < MAX_NUMS; i++) {
        struct set* s = &sets[i];
        free(s->numbers);
    }
}

void clear_sets() {
    for (int i = 0; i < numc; i++) {
        struct set* s = sets+i;

        set_ptrs[i] = s;

        s->numbers[0] = i+1;
        s->size = 1;
    }
}

void remove_number(struct set* s, int num) {
    int index = 0;
    while (index < s->size) {
        if (s->numbers[index] == num) {
            break;
        } else {
            index++;
        }
    }

    s->size--;
    for (int i = index; i < s->size; i++) {
        s->numbers[i] = s->numbers[i+1];
    }
}

void insert_number(struct set* s, int num) {
    s->size++;

    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->numbers = realloc(s->numbers, sizeof(int)*s->capacity);
    }

    s->numbers[s->size-1] = num;

    set_ptrs[num-1] = s;
}

void set_union(int p, int q) {
#ifdef DEBUG
    printf("union: %d %d\n", p, q);
#endif
    struct set* src = set_ptrs[p-1];
    struct set* dst = set_ptrs[q-1];
    if (dst->size < src->size) {
        src = set_ptrs[q-1];
        dst = set_ptrs[p-1];
    }

    if (src != dst) {
        for (int i = 0; i < src->size; i++) {
            insert_number(dst, src->numbers[i]);
        }
    }
}

void set_move(int p, int q) {
#ifdef DEBUG
    printf("move: %d -> %d\n", p, q);
#endif
    struct set* src = set_ptrs[p-1];
    struct set* dst = set_ptrs[q-1];

    if (src != dst) {
        remove_number(src, p);
        insert_number(dst, p);
    }
}

void set_print(int p) {
#ifdef DEBUG
    printf("print: %d\n", p);
#endif
    struct set* s = set_ptrs[p-1];

    int sum = 0;
    for (int i = 0; i < s->size; i++) {
        sum += s->numbers[i];
    }

    printf("%d %d\n", s->size, sum);
}

int main() {
    create_sets();

    int cmdc;
    while (scanf("%d%d", &numc, &cmdc) == 2) {
#ifdef DEBUG
            printf("case: %d %d\n", numc, cmdc);
#endif
        clear_sets();
        set_debug();

        for (int i = 0; i < cmdc; i++) {
            int command, p, q;
            scanf("%d", &command);

            switch (command) {
            case 1:
                scanf("%d%d", &p, &q);
                set_union(p, q);
                break;
            case 2:
                scanf("%d%d", &p, &q);
                set_move(p, q);
                break;
            case 3:
                scanf("%d", &p);
                set_print(p);
            }

            set_debug();
        }
    }

    destroy_sets();

    return 0;
}
