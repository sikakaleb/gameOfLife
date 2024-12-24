#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board* createBoard(int width, int height) {
    Board* b = malloc(sizeof(Board));
    b->width = width;
    b->height = height;
    b->cells = malloc(width * height * sizeof(CellState));
    for(int i = 0; i < width * height; i++) {
        b->cells[i] = DEAD;
    }
    return b;
}

void freeBoard(Board* b) {
    if(b) {
        free(b->cells);
        free(b);
    }
}

Board* loadBoardFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if(!f) return NULL;
    int w, h;
    if(fscanf(f, "%d %d", &w, &h) != 2) {
        fclose(f);
        return NULL;
    }
    Board* b = createBoard(w, h);
    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            int val;
            if(fscanf(f, "%d", &val) != 1) {
                freeBoard(b);
                fclose(f);
                return NULL;
            }
            b->cells[y * w + x] = val ? ALIVE : DEAD;
        }
    }
    fclose(f);
    return b;
}

int saveBoardToFile(const Board* b, const char* filename) {
    FILE* f = fopen(filename, "w");
    if(!f) return 0;
    fprintf(f, "%d %d\n", b->width, b->height);
    for(int y = 0; y < b->height; y++) {
        for(int x = 0; x < b->width; x++) {
            CellState c = b->cells[y * b->width + x];
            fprintf(f, "%d ", (c == ALIVE) ? 1 : 0);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    return 1;
}

Board* copyBoard(const Board* src) {
    if(!src) return NULL;
    Board* copy = createBoard(src->width, src->height);
    for(int i = 0; i < src->width * src->height; i++) {
        copy->cells[i] = src->cells[i];
    }
    return copy;
}
