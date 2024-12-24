#include <SDL_events.h>
#include <SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>       // pour clock / SDL_Delay
#include "src/board.h"
#include "src/rules.h"
#include "src/history.h"
#include "src/graphics.h"

int main() {
    Board* initial = loadBoardFromFile("../resources/grid.txt");
    if(!initial) {
        printf("Failed to load grid.txt\n");
        return 1;
    }

    History* history = createHistory(50); // un peu plus grand que 10
    pushGeneration(history, initial);
    freeBoard(initial);

    // On réduit un peu la taille des cellules pour voir un plateau plus grand
    int cellSize = 10;
    int offsetX = 10;
    int offsetY = 10;

    // On calcule la taille de la fenêtre
    int windowWidth = history->states[0]->width * cellSize + 2 * offsetX;
    int windowHeight = history->states[0]->height * cellSize + 2 * offsetY;

    // Pour éviter une fenêtre minuscule, on peut forcer une taille min
    if (windowWidth < 600)  windowWidth = 600;
    if (windowHeight < 400) windowHeight = 400;

    if(initSDL(windowWidth, windowHeight) < 0) {
        printf("Could not initialize SDL.\n");
        freeHistory(history);
        return 1;
    }

    int quit = 0;
    int autoPlay = 0; // 0 = pause, 1 = play

    // Pour gérer l'autoPlay : un timer
    Uint32 lastStepTime = SDL_GetTicks();
    Uint32 stepDelay = 200; // 200 ms = 5 générations / seconde

    while(!quit) {
        // On gère d'abord les événements (clavier, souris, etc.)
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quit = 1;
            }
            else if(e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
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
                    case SDLK_SPACE: {
                        Board* current = getCurrentBoard(history);
                        if(current) {
                            Board* next = createBoard(current->width, current->height);
                            nextGeneration(current, next);
                            pushGeneration(history, next);
                            freeBoard(next);
                        }
                    } break;
                    case SDLK_p:
                        // toggle autoPlay
                        autoPlay = !autoPlay;
                        printf("autoPlay = %d\n", autoPlay);
                        break;
                    default:
                        break;
                }
            }
        }

        // Si on est en mode autoPlay et que stepDelay ms se sont écoulées,
        // on calcule la génération suivante automatiquement
        if(autoPlay) {
            Uint32 now = SDL_GetTicks();
            if(now - lastStepTime >= stepDelay) {
                Board* current = getCurrentBoard(history);
                if(current) {
                    Board* next = createBoard(current->width, current->height);
                    nextGeneration(current, next);
                    pushGeneration(history, next);
                    freeBoard(next);
                }
                lastStepTime = now;
            }
        }

        // On rend le Board courant
        Board* current = getCurrentBoard(history);
        if(current) {
            renderBoard(current, cellSize, offsetX, offsetY);
        }

        // Petit "yield" pour éviter de saturer le CPU
        SDL_Delay(10);
    }

    closeSDL();
    freeHistory(history);
    return 0;
}
