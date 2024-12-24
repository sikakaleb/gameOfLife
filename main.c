#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/board.h"
#include "src/rules.h"
#include "src/history.h"

static void printBoard(const Board* b) {
    if(!b) return;
    for(int y = 0; y < b->height; y++) {
        for(int x = 0; x < b->width; x++) {
            printf("%c", b->cells[y * b->width + x] == ALIVE ? 'O' : '.');
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    Board* initial = loadBoardFromFile("grid.txt");
    if(!initial) {
        printf("Unable to load grid.txt\n");
        return 1;
    }

    History* history = createHistory(10);
    pushGeneration(history, initial);
    freeBoard(initial);

    while(1) {
        Board* current = getCurrentBoard(history);
        if(!current) {
            printf("No board loaded.\n");
            break;
        }

        printf("Current generation index: %d\n", history->currentIndex);
        printBoard(current);
        printf("Commands: [n] next, [p] previous, [s] step forward, [S] save all, [q] quit\n> ");

        char cmd[10];
        if(!fgets(cmd, sizeof(cmd), stdin)) {
            break;
        }
        if(cmd[0] == 'q') {
            break;
        }
        if(cmd[0] == 'p') {
            if(canGoPrevious(history)) {
                goPrevious(history);
            } else {
                printf("Can't go to previous generation.\n");
            }
        } else if(cmd[0] == 'n') {
            if(canGoNext(history)) {
                goNext(history);
            } else {
                printf("Can't go to next generation.\n");
            }
        } else if(cmd[0] == 's') {
            Board* next = createBoard(current->width, current->height);
            nextGeneration(current, next);
            pushGeneration(history, next);
            freeBoard(next);
        } else if(cmd[0] == 'S') {
            saveAllGenerations(history);
            printf("All generations saved.\n");
        }
    }

    freeHistory(history);
    return 0;
}
