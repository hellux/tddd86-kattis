/*
 * Algorithm
 * -load values into data structures
 *  -stack is fixed array
 *  -queue is fixed array
 *  -pueue is fixed array heap
 * -compare output with given values
 */
#include <stdio.h>
#include <stdbool.h>

#define MAX_INSTR 1001

int insert_pos(int array[], int start, int end, int value) {
    while (start < end) {
        int middle = (start + end) / 2;
        int current = array[middle];

        if (current > value) {
            start = middle + 1;
        } else if (value > current) {
            end = middle;
        } else {
            return middle;
        }
    }
    return start;
}

struct stack {
    int block[MAX_INSTR];
    int top;
};
void s_reset(struct stack* s) {
    s->top = 1;
    s->block[s->top-1] = -1;
}
void s_push(struct stack* s, int value) { s->block[s->top++] = value; }
int s_pop(struct stack* s) { return s->block[--s->top]; }

struct queue {
    int block[MAX_INSTR];
    int start;
    int end;
};
void q_reset(struct queue* q) {
    q->start = q->end = 0;
}
void q_push(struct queue* q, int value) { q->block[q->end++] = value; }
int q_pop(struct queue* q) { return q->block[q->start++]; }

struct pueue {
    int block[MAX_INSTR];
    int size;
};
void p_reset(struct pueue* p) {
    p->size = 0;
}
void p_push(struct pueue* p, int value) {
    int current = p->size++;
    int parent = (current-1) >> 1;
    while (p->block[parent] < value && parent >= 0) {
        p->block[current] = p->block[parent];
        current = parent;
        parent = (current-1) >> 1;
    }
    p->block[current] = value;
}
int p_pop(struct pueue* p) {
    int value = p->block[0];
    p->block[0] = p->block[--p->size];
    int current = 0;
    int max = current << 1;
    max += (p->block[max+1] > p->block[max+2]) ? 1 : 2;

    while (p->block[max] > p->block[current] && max < p->size) {
        int tmp = p->block[max];
        p->block[max] = p->block[current];
        p->block[current] = tmp;

        current = max;
        max = current << 1;
        max += (p->block[max+1] > p->block[max+2]) ? 1 : 2;
    }
    return value;
}
void p_show(struct pueue* p) {
    printf("( ");
    for (int i = 0; i < p->size; i++) {
        printf("%d ", p->block[i]);
    }
    printf(")\n");
}

int main() {
    char* type_strings[] = {"stack", "queue", "priority queue"};
    struct stack s;
    struct queue q;
    struct pueue p;

    int n;
    while (scanf("%d", &n) == 1) {
        bool type[3] = {true, true, true};
        s_reset(&s);
        q_reset(&q);
        p_reset(&p);
        for (int i = 0; i < n; i++) {
            int command, value;
            scanf("%d%d", &command, &value);
            if (command == 1) {
                if (type[0]) s_push(&s, value);
                if (type[1]) q_push(&q, value);
                if (type[2]) p_push(&p, value);
            } else {
                if (type[0]) if (value != s_pop(&s)) type[0] = false;
                if (type[1]) if (value != q_pop(&q)) type[1] = false;
                if (type[2]) if (value != p_pop(&p)) type[2] = false;
            }
        }

        int used_type = 0;
        int used_types = 0;
        for (int i = 0; i < 3; i++) {
            if (type[i]) {
                used_types++;
                used_type = i;
            }
        }

        switch (used_types) {
        case 0:
            printf("impossible\n");
            break;
        case 1:
            printf("%s\n", type_strings[used_type]);
            break;
        default:
            printf("not sure\n");
        }
    }
    return 0;
}
