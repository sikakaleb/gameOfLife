#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

History* createHistory(int initialCapacity) {
    History* h = malloc(sizeof(History));
    h->capacity = initialCapacity;
    h->count = 0;
    h->currentIndex = -1;
    h->states = malloc(sizeof(Board*) * initialCapacity);
    return h;
}

void freeHistory(History* h) {
    if(h) {
        for(int i = 0; i < h->count; i++) {
            freeBoard(h->states[i]);
        }
        free(h->states);
        free(h);
    }
}

static void resizeHistory(History* h) {
    h->capacity *= 2;
    h->states = realloc(h->states, sizeof(Board*) * h->capacity);
}

void pushGeneration(History* h, const Board* b) {
    // On supprime les états "en aval" si l'utilisateur a fait un "previous"
    if(h->currentIndex < h->count - 1) {
        for(int i = h->currentIndex + 1; i < h->count; i++) {
            freeBoard(h->states[i]);
        }
        h->count = h->currentIndex + 1;
    }
    if(h->count >= h->capacity) {
        resizeHistory(h);
    }
    Board* copy = copyBoard(b);
    h->states[h->count] = copy;
    h->count++;
    h->currentIndex = h->count - 1;
}

Board* getCurrentBoard(const History* h) {
    if(!h || h->currentIndex < 0 || h->currentIndex >= h->count) {
        return NULL;
    }
    return h->states[h->currentIndex];
}

int canGoPrevious(const History* h) {
    return (h->currentIndex > 0);
}

int canGoNext(const History* h) {
    return (h->currentIndex < h->count - 1);
}

void goPrevious(History* h) {
    if(canGoPrevious(h)) {
        h->currentIndex--;
    }
}

void goNext(History* h) {
    if(canGoNext(h)) {
        h->currentIndex++;
    }
}

void saveAllGenerations(const History* h) {
    for(int i = 0; i < h->count; i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "save_gen_%d.txt", i);
        saveBoardToFile(h->states[i], filename);
    }
}
