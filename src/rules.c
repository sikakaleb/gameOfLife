#include "rules.h"

static int countAliveNeighbors(const Board* b, int x, int y) {
    int count = 0;
    for(int dy = -1; dy <= 1; dy++) {
        for(int dx = -1; dx <= 1; dx++) {
            if(dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if(nx >= 0 && nx < b->width && ny >= 0 && ny < b->height) {
                if(b->cells[ny * b->width + nx] == ALIVE) {
                    count++;
                }
            }
        }
    }
    return count;
}

void nextGeneration(const Board* oldB, Board* newB) {
    for(int y = 0; y < oldB->height; y++) {
        for(int x = 0; x < oldB->width; x++) {
            CellState current = oldB->cells[y * oldB->width + x];
            int neighbors = countAliveNeighbors(oldB, x, y);
            if(current == ALIVE) {
                if(neighbors == 2 || neighbors == 3) {
                    newB->cells[y * newB->width + x] = ALIVE;
                } else {
                    newB->cells[y * newB->width + x] = DEAD;
                }
            } else {
                if(neighbors == 3) {
                    newB->cells[y * newB->width + x] = ALIVE;
                } else {
                    newB->cells[y * newB->width + x] = DEAD;
                }
            }
        }
    }
}
