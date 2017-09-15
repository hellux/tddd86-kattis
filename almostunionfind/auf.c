#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMS 100001
#define INIT_CAP 10

struct set {
    int* numbers;
    int size;
    int capacity;
};

struct set sets[MAX_NUMS];
struct set* set_ptrs[MAX_NUMS]; /* index = num-1 pointing to its set */
int numc;

void set_debug() {
    for (int i = 0; i < numc; i++) {
        struct set* s = set_ptrs[i];
        printf("%d: ( ", i+1);
        for (int i = 0; i < s->size; i++) {
            printf("%d ", s->numbers[i]);
        }
        printf(") \n");
    }
}

void create_sets() {
    for (int i = 0; i < MAX_NUMS; i++) {
        struct set* s = &sets[i];
        s->numbers = malloc(sizeof(int)*INIT_CAP);
        s->capacity = INIT_CAP;
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
        struct set* s = &sets[i];
        set_ptrs[i] = s;

        s->size = 1;
        s->numbers[0] = i+1;
    }
}

void remove_number(struct set* s, int num) {
    int index = 0;
    while (index < s->size) {
        if (s->numbers[index] == num) break;
    }

    s->size--;
    for (int i = index; i < s->size; i++) {
        s->numbers[i] = s->numbers[i+1];
    }
}

void insert_number(struct set* s, int num) {
    s->numbers[s->size++] = num;

    if (s->size == s->capacity) {
        s->capacity *= 2;
        s->numbers = realloc(s->numbers, sizeof(int)*s->capacity);
    }
}

void move_number(struct set* src, struct set* dest, int num) {
    remove_number(src, num);
    insert_number(dest, num);
    set_ptrs[num-1] = dest;
}

void set_union(int p, int q) {
    struct set* src = set_ptrs[p-1];
    struct set* dest = set_ptrs[q-1];

    if (dest->size <= src->size) {
        src = set_ptrs[q-1];
        dest = set_ptrs[p-1];
    } 

    if (src != dest) {
        for (int i = 0; i < src->size; i++) {
            move_number(src, dest, src->numbers[i]);
        }
    }
}

void set_move(int p, int q) {
    struct set* src = set_ptrs[p-1];
    struct set* dest = set_ptrs[q-1];

    if (src != dest) {
        move_number(src, dest, p);
    }
}

void set_print(int p) {
    struct set* s = set_ptrs[p-1];

    int sum = 0;
    for (int i = 0; i < s->size; i++) {
        sum += s->numbers[i];
    }

    printf("%d %d\n", s->size, sum);
}

int main() {
    create_sets();

    int commc;
    while (scanf("%d%d", &numc, &commc) == 2) {
        clear_sets();

        for (int i = 0; i < commc; i++) {
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
        }
    }

    destroy_sets();
}
