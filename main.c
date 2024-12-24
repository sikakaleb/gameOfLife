#include <stdio.h>
#include <stdlib.h>
#include "src/board.h"
#include "src/rules.h"

static void printBoard(const Board* b) {
    for(int y = 0; y < b->height; y++) {
        for(int x = 0; x < b->width; x++) {
            CellState c = b->cells[y * b->width + x];
            printf("%c", c == ALIVE ? 'O' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    Board* board = loadBoardFromFile("../resources/grid.txt");
    if(!board) {
        printf("Error loading board.\n");
        return 1;
    }
    printBoard(board);

    int generations = 3;
    for(int i = 0; i < generations; i++) {
        Board* next = createBoard(board->width, board->height);
        nextGeneration(board, next);
        freeBoard(board);
        board = next;
        printBoard(board);
    }

    saveBoardToFile(board, "../out/output.txt");
    freeBoard(board);
    return 0;
}
