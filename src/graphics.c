#include <SDL2/SDL.h>
#include "graphics.h"
#include "rules.h"

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static int gScreenWidth = 800;
static int gScreenHeight = 600;

int initSDL(int width, int height) {
    gScreenWidth = width;
    gScreenHeight = height;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }
    gWindow = SDL_CreateWindow("Game Of Life",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               gScreenWidth, gScreenHeight,
                               SDL_WINDOW_SHOWN);
    if(!gWindow) {
        SDL_Quit();
        return -1;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!gRenderer) {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return -1;
    }
    return 0;
}

void closeSDL() {
    if(gRenderer) {
        SDL_DestroyRenderer(gRenderer);
        gRenderer = NULL;
    }
    if(gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = NULL;
    }
    SDL_Quit();
}

void renderBoard(const Board* b, int cellSize, int offsetX, int offsetY) {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);

    for(int y = 0; y < b->height; y++) {
        for(int x = 0; x < b->width; x++) {
            CellState state = b->cells[y * b->width + x];
            if(state == ALIVE) {
                SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255); // Vert
            } else {
                SDL_SetRenderDrawColor(gRenderer, 50, 50, 50, 255); // Gris
            }
            SDL_Rect cellRect;
            cellRect.x = offsetX + x * cellSize;
            cellRect.y = offsetY + y * cellSize;
            cellRect.w = cellSize;
            cellRect.h = cellSize;
            SDL_RenderFillRect(gRenderer, &cellRect);
        }
    }

    SDL_RenderPresent(gRenderer);
}

int handleEvents(History* history) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) {
            return 1; // quitter
        }
        if(e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return 1;
                case SDLK_LEFT:
                    if(canGoPrevious(history)) {
                        goPrevious(history);
                    }
                    break;
                case SDLK_RIGHT:
                    if(canGoNext(history)) {
                        goNext(history);
                    }
                    break;
                case SDLK_SPACE:
                {
                    Board* current = getCurrentBoard(history);
                    if(current) {
                        Board* next = createBoard(current->width, current->height);
                        nextGeneration(current, next);
                        pushGeneration(history, next);
                        freeBoard(next);
                    }
                }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
