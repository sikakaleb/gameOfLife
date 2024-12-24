#ifndef HISTORY_H
#define HISTORY_H

#include "board.h"

typedef struct {
    Board** states;
    int capacity;
    int count;
    int currentIndex;
} History;

History* createHistory(int initialCapacity);
void freeHistory(History* h);

/* Ajoute une copie du Board à la suite de l'historique
   et met à jour currentIndex. */
void pushGeneration(History* h, const Board* b);

/* Renvoie un pointeur vers la Board courante. */
Board* getCurrentBoard(const History* h);

/* Vérifie s'il est possible de reculer. */
int canGoPrevious(const History* h);

/* Vérifie s'il est possible d'avancer. */
int canGoNext(const History* h);

/* Décrémente currentIndex si possible. */
void goPrevious(History* h);

/* Incrémente currentIndex si possible. */
void goNext(History* h);

/* Sauvegarde toutes les générations dans plusieurs fichiers distincts :
   save_gen_0.txt, save_gen_1.txt, ... */
void saveAllGenerations(const History* h);

#endif
