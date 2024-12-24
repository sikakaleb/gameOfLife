#ifndef BOARD_H
#define BOARD_H

typedef enum {
 DEAD,
 ALIVE
} CellState;

typedef struct {
 int width;
 int height;
 CellState* cells;
} Board;

Board* createBoard(int width, int height);
void freeBoard(Board* b);
Board* loadBoardFromFile(const char* filename);
int saveBoardToFile(const Board* b, const char* filename);

#endif
