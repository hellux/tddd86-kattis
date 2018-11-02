#include <stdio.h>
#include <stdbool.h>

#define WIDTH 5
#define HEIGHT 5
#define MAX_MOVES 10

int main(int argc, char* args[]) {

    int cases;
    scanf("%d\n", &cases);

    for (int i = 0; i < cases; i++) {
        char board[HEIGHT][WIDTH];
        int x, y;
        for (int row = 0; row < HEIGHT; row++) {
            char row_buffer[WIDTH+1];
            fgets(row_buffer, WIDTH+2, stdin); /* line, '\n', '\0' */
            for (int col = 0; col < WIDTH; col++) {
                board[row][col] = row_buffer[col];
                if (board[row][col] == ' ') {
                    x = col;
                    y = row;
                }
            }
        }

        int moves = 0;
        while (moves < MAX_MOVES) {
            
        }
    }
    
    return 0;
}
