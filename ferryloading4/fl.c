#include <stdio.h>
#include <stdbool.h>

#define MAX_CARS 10000

struct queue left;
struct queue right;

/*
 * Queue with consant memory block
 * push and pop by modifying start and end indicators
 * - end points to address after first element
 * - start points to first element (end if empty)
 */
struct queue {
    int cars[MAX_CARS];
    int start;
    int end;
};
struct queue* queues(char bank) { return bank == 'l' ? &left : &right; }
void reset(struct queue* q) { q->start = 0; q->end = 0; }
bool nonempty(struct queue* q) { return (q->end - q->start) != 0; }
void push(struct queue* q, int car) { q->cars[q->end++] = car; }
void pop(struct queue* q) { q->start++; }
int front(struct queue* q) { return q->cars[q->start]; }

int main(int argc, char* args[]) {
    int tests;
    scanf("%d", &tests);

    for (int i = 0; i < tests; i++) {
        int length;
        int cars;
        scanf("%d%d", &length, &cars);
        length *= 100;

        reset(queues('l'));
        reset(queues('r'));
        for (int c = 0; c < cars; c++) {
            int car_length;
            char car_bank[6];
            scanf("%d%s", &car_length, car_bank);
            push(queues(car_bank[0]), car_length);
        }
        
        char bank = 'l';
        int space = length;
        int trips = 1;
        while (nonempty(queues('l')) || nonempty(queues('r'))) {
            if (nonempty(queues(bank)) && front(queues(bank)) <= space) {
                space -= front(queues(bank));
                pop(queues(bank));
            } else {
                bank = (bank == 'l' ? 'r' : 'l');
                trips++;
                space = length;
            }
        }

        printf("%d\n", trips);
    }

    return 0;
}
