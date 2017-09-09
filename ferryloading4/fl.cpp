#include <iostream>
#include <queue>
#include <map>

using namespace std;

int main(int argc, char* args[]) {
    int tests;
    scanf("%d", &tests);

    for (int i = 0; i < tests; i++) {
        int length;
        int cars;
        scanf("%d%d", &length, &cars);
        length *= 100;

        map<char, queue<int>> queues;
        queues['l'];
        queues['r'];
        
        for (int c = 0; c < cars; c++) {
            int car_length;
            char car_bank[6];
            scanf("%d%s", &car_length, car_bank);
            queues[car_bank[0]].push(car_length);
        }

        char bank = 'l';
        int space = length;
        int trips = 1;

        while (!queues['l'].empty() || !queues['r'].empty()) {
            if (!queues[bank].empty() && queues[bank].front() <= space) {
                space -= queues[bank].front();
                queues[bank].pop();
            } else {
                bank = (bank == 'l' ? 'r' : 'l');
                trips++;
                space = length;
            }
        }

        printf("%d\n", trips);
    }

    return EXIT_SUCCESS;
}
