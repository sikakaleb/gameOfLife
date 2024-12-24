#include <stdio.h>
#include <stdlib.h>
#include "src/board.h"
#include "src/rules.h"
#include "src/history.h"
#include "src/graphics.h"

int main() {
    Board* initial = loadBoardFromFile("grid.txt");
    if(!initial) {
        printf("Failed to load grid.txt\n");
        return 1;
    }

    History* history = createHistory(10);
    pushGeneration(history, initial);
    freeBoard(initial);

    int cellSize = 20; // taille en pixels d'une cellule
    int offsetX = 10;  // marge à gauche
    int offsetY = 10;  // marge en haut

    int windowWidth = history->states[0]->width * cellSize + 2 * offsetX;
    int windowHeight = history->states[0]->height * cellSize + 2 * offsetY;

    if(initSDL(windowWidth, windowHeight) < 0) {
        printf("Could not initialize SDL.\n");
        freeHistory(history);
        return 1;
    }

    int quit = 0;
    while(!quit) {
        Board* current = getCurrentBoard(history);
        if(current) {
            renderBoard(current, cellSize, offsetX, offsetY);
        }
        quit = handleEvents(history);
    }

    closeSDL();
    freeHistory(history);
    return 0;
}
