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
#define MAX_CARATTERI_PASSWORD 20 //caratteri massimi per la password dell'admin,anche se la password è minore di 20 caratteri non si esclude una possibile modifica di questa
#define MAX_CARATTERI_DESCRIZIONI 200 //caratteri massimi per la recensione e descrizione
#define MAX_GENERI 5 //Numero massimo di generi inseribili
#define MAX_RECENSIONI 70 //Numero massimo di recensioni inseribili per ogni gioco, che sia un valore accettabile
#define MAX_PRODUCTION 100 // Numero massimo di copie distribuite, per evitare valori eccessivi
#define MAX_GIOCHI 50  // Giochi massimi per il catalogo nell'ordinamento, si presuppone non si vada oltre
typedef struct{
    int recensione_num; // 0-5, obbligatoria
    char recensione_scritta[MAX_CARATTERI_DESCRIZIONI]; //Facoltativa
}recensione_t;
//Struttura per i videogiochi
typedef struct {
    char nome[80]; // aumentato per gestire nomi lunghi
    char editore[50]; // aumentato per gestire nomi lunghi
    char sviluppatore[50]; // aumentato per gestire nomi lunghi
    char descrizione_breve_gioco[MAX_CARATTERI_DESCRIZIONI]; // facoltativa
    int anno_uscita;
    char genere[MAX_GENERI][MAX_CARATTERI_DESCRIZIONI]; // dimensioni corrette per evitare overflow
    recensione_t recensione[MAX_RECENSIONI]; // array di recensioni, ogni gioco può avere più recensioni
    int copie_vendute; // contatore degli acquisti -> utile per le statistiche
} videogame_t;

//Funzione per la gestione del menu
void MenuPrincipale(videogame_t videogame);
void MenuAdmin(videogame_t videogame, char *nomeFile, short);
void MenuVisitatore(videogame_t videogame, char *nomeFile, short);
int AutenticazioneAdmin();

//Funzioni per la gestione del catalogo
void ScriviCatalogo(char *nomeFile);
void Ricerca(char *nomeFile, videogame_t, short);
void VisualizzaCat(char *nomeFile, videogame_t);

//Funzioni per la gestione dei videogiochi da parte dell'admin
void ModificaGioco(char *nomeFile, char*,videogame_t, short);
void CancellaGioco(char *nomeFile, char*,videogame_t, short);
void AggiungiGioco(char *nomeFile, videogame_t);

//Funzioni per la gestione dei videogiochi da parte dell'utente
void AcquistaGioco(char *nomeFile, char*,videogame_t, short);
void VisualizzaVideogioco(char *nomeFile, char*,videogame_t);
void AggiungiRecensione(char *nomeFile, char*,videogame_t, short);

//Funzioni per la gestione dei videogiochi per entrambi i ruoli
void Visualizza_Recensione(char *nomeFile, char*,videogame_t);
float StatisticaRecensione(char *nomeFile, char*, videogame_t);
float StatisticaCopieVendute(char *nomeFile, char*, videogame_t);

//Funzioni per l'ordinamento
void Ordinamento_copie_vendute(char *nomeFile, videogame_t);
void Ordinamento_statistiche(char *nomeFile, videogame_t);

#endif