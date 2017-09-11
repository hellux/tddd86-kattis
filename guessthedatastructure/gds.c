#include <stdio.h>
#include <stdbool.h>

#define MAX_INSTR 2000

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
    s->top = MAX_INSTR / 2;
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
    q->start = q->end = MAX_INSTR / 2;
    q->block[q->start] = -1; 
}
void q_push(struct queue* q, int value) { q->block[q->end++] = value; }
int q_pop(struct queue* q) { return q->block[q->start++]; }

struct pueue {
    int block[MAX_INSTR];
    int start;
    int end;
};
void p_reset(struct pueue* p) {
    p->start = p->end = MAX_INSTR / 2;
    p->block[p->start] = -1; 
}
void p_push(struct pueue* p, int value) {
    int pos = insert_pos(p->block, p->start, p->end, value);
    for (int i = p->end++; i > pos; i--) {
        p->block[i] = p->block[i-1];
    }
    p->block[pos] = value;
}
int p_pop(struct pueue* p) { return p->block[p->start++]; }

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
                s_push(&s, value);
                q_push(&q, value);
                p_push(&p, value);
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
