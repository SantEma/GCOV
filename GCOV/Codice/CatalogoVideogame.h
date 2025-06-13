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

//Costanti utili per il programma
#define GIOCHI_START 20 //Numero giochi presenti nel file inizialmente
#define PASSWORD "Admin157" //codice per accedere come admin, altrimenti si è ospiti (di solito non andrebbero mai messe hardcode le password, ma per semplicità lo si implementa in questa maniera)
#define MAX_CARATTERI_PASSWORD 10 //caratteri massimi per la password
#define MAX_CARATTERI_DESCRIZIONI 200 //caratteri massimi per la recensione e descrizione
#define MAX_RECENSIONI 5 //Numero massimo di recensioni inseribili

//Struttura per i videogiochi
typedef struct {
    char nome[70]; // gioco col nome più lungo al mondo
    char editore[40]; // editore col nome più lungo al mondo
    char sviluppatore[40];
    char descrizione_breve_gioco[MAX_CARATTERI_DESCRIZIONI]; // facoltativa
    int anno_uscita;
    char genere[MAX_CARATTERI_DESCRIZIONI][MAX_RECENSIONI]; // anche più di una
    recensione_t recensione; 
    int copie_vendute; // contatore degli acquisti -> utile per le statistiche
} videogame_t;

//Struttura per le recensioni
typedef struct{
    int recensione_num; // 0-5, obbligatoria
    char recensione_scritta[MAX_CARATTERI_DESCRIZIONI]; //Facoltativa
}recensione_t;


//Funzione per la gestione del menu
<<<<<<< Updated upstream
<<<<<<< Updated upstream
void MenuPrincipale(videogame_t videogame);
void MenuAdmin(videogame_t videogame, char *nomeFile);
void MenuVisitatore(videogame_t videogame, char *nomeFile);
=======
void MenuPrincipale();
void MenuAdmin();
void MenuVisitatore();
>>>>>>> Stashed changes
=======
void MenuPrincipale();
void MenuAdmin();
void MenuVisitatore();
>>>>>>> Stashed changes

//Funzioni per la gestione del catalogo
void ScriviCatalogo(char *nomeFile);
void RicercaAdmin(char *nomeFile, videogame_t);
void RicercaVisitatore(char *nomeFile, videogame_t);

//Funzioni per la gestione dei videogiochi da parte dell'admin
void ModificaGioco(char *nomeFile, videogame_t, char*);
void CancellaGioco(char *nomeFile, videogame_t, char*);
void AggiungiGioco(char *nomeFile, videogame_t);
#endif