#include <stdlib.h>
#include <stdio.h>

#define MAX_CARS 10000

void sail(int* trips, char* bank, int* space, int length) {
    *(trips) += 1;
    *bank = *bank == 'l' ? 'r' : 'l';
    *space = length;
}

int main(int argc, char* args[]) {
    int tests;
    scanf("%d", &tests);

    for (int i = 0; i < tests; i++) {
        int length;
        int cars;
        scanf("%d%d", &length, &cars);
        length *= 100;

        char bank = 'l';
        int space = length;
        int trips = 0;
        //int buffer_l[MAX_CARS];
        //int buffer_r[MAX_CARS];
        for (int c = 0; c < cars; c++) {
            int car_length;
            char car_bank[6];
            scanf("%d%s", &car_length, car_bank);

            if (car_bank[0] == bank) {
                if (car_length <= space) {
                    space -= car_length;
                } else {
                    sail(&trips, &bank, &space, length);
                }
            } else {
                sail(&trips, &bank, &space, length);
            }
        }

        printf("%d\n", trips);
    }

    return EXIT_SUCCESS;
}
