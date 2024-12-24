#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "board.h"
#include "history.h"

/*
 * Initialise SDL (fenêtre, renderer).
 * Retourne 0 si succès, -1 sinon.
 */
int initSDL(int width, int height);

/*
 * Ferme SDL (renderer, fenêtre, etc.).
 */
void closeSDL();

/*
 * Affiche le Board courant dans la fenêtre.
 * - cellSize : taille en pixels d'une cellule
 * - offsetX, offsetY : décalage en pixels pour l'affichage
 */
void renderBoard(const Board* b, int cellSize, int offsetX, int offsetY);

/*
 * Attends les événements SDL, et met à jour l'historique
 * ou la boucle du programme selon l'entrée utilisateur.
 * Retourne 0 si on doit continuer, 1 si on doit quitter.
 */
int handleEvents(History* history);

#endif
