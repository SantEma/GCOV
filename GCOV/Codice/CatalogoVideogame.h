/**
 * @file catalogoVideogame.h
 * @author Andrea Milo
 * @brief Definizione della struttura e delle funzioni per la gestione di un catalogo di videogiochi ...
 * @version 0.1
 * @date 2025-05-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef CATALOGOVIDEOGAME_H
#define CATALOGOVIDEOGAME_H

//costanti
#define GIOCHI_START 20 //numero giochi presenti nel file inizialmente
#define PASSWORD "Admin157" //codice per accedere come admin, altrimenti si è ospiti (di solito non andrebbero mai messe hardcode le password)

//struttura per i videogiochi
typedef struct {
    char nome[70]; // gioco col nome più lungo al mondo
    char editore[40]; // editore col nome più lungo al mondo
    char sviluppatore[40];
    char descrizione_breve_gioco[50]; // facoltativa
    int anno_uscita;
    char genere[20]; // anche più di una
    int recensione; // 0-5, obbligatoria
    int copie_vendute; // utile per le statistiche
} videogame_t;

//funzione per la gestione del menu
int Menu();

//funzioni per la gestione del catalogo
void ScriviCatalogo(char *nomeFile);
void RicercaAdmin(char *nomeFile, videogame_t);
void RicercaVisitatore(char *nomeFile,videogame_t);

//funzioni per la gestione dei videogiochi da parte dell'admin
void ModificaGioco(char *nomeFile, videogame_t, char);
void CancellaGioco(char *nomeFile, videogame_t, char);
void AggiungiGioco(char *nomeFile, videogame_t, char);
#endif