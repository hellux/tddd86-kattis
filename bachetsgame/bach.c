#include <stdio.h>
#include <stdbool.h>

#define MAX_AMOUNTS 10
#define MAX_STONES 1000000

int main(int argc, char* args[]) {
    int amounts[MAX_AMOUNTS];
    bool wins[MAX_STONES+1];
    wins[0] = false;

    int stones;
    int amounts_size;

    while (scanf("%d%d", &stones, &amounts_size) == 2) {
        for (int a = 0; a < amounts_size; a++) {
            scanf("%d", amounts+a);
        }

        for (int i = 1; i <= stones; i++) {
            wins[i] = false;
            for (int a = 0; a < amounts_size; a++) {
                int index = i - amounts[a];
                if (index >= 0 && !wins[index]) {
                    wins[i] = true;
                    break;
                }
            }
        }
        
        printf("%s wins\n", wins[stones] ? "Stan" : "Ollie");
        fflush(stdout);
    }

    return 0;
}
