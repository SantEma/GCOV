/**
 * @file catalogoVideogame.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef CATALOGOVIDEOGAME_H
#define CATALOGOVIDEOGAME_H

typdef struct {
    char nome[50];
    char editore[20];
    char sviluppatore[20];
    char descrizione_gioco[20]; // facoltativa
    int anno_uscita;
    char genere[20]; // anche più di uno
    int recensione; // 0-5
} Videogame;

#endif