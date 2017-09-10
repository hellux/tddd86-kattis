/*
 * Algorithm:
 * Calculates winner by going backwards from the end of the game,
 * where winner is certain.
 * 
 * -iterate through every game state (stones left) from 0 stones up to given
 *  -check if you can jump to a certain loss state (for opponent)
 *   (0 is loss at start). if yes then flag state as win, otherwise loss
 *
 *
 * TODO: the pattern usually repeats, find general rule for all sets
 */
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
