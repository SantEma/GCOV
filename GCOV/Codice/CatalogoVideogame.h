/**
 * @file catalogoVideogame.h
 * @author Andrea Milo & Emanuele Santoruvo
 * @brief Definizione della struttura, costanti e delle funzioni per la gestione di un catalogo di videogiochi
 * @version 1.1
 * @date 2025-06-25
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef CATALOGOVIDEOGAME_H
#define CATALOGOVIDEOGAME_H

/**
 * @brief Costanti utilizzate nel programma per la gestione del catalogo dei videogiochi, l'acquisto, le recensioni e l'autenticazione dell'admin.
 * Queste costanti definiscono i limiti e le caratteristiche del catalogo, come il numero massimo di giochi, la lunghezza delle password.
 *
 */
//Costanti utili per il programma
#define GIOCHI_START 20 //Numero giochi presenti nel file inizialmente
#define PASSWORD "Admin157" //codice per accedere come admin, altrimenti si è ospiti (di solito non andrebbero mai messe hardcode le password, ma per semplicità lo si implementa in questa maniera)
#define MAX_CARATTERI_PASSWORD 15 //caratteri massimi per la password dell'admin
#define MAX_CARATTERI_DESCRIZIONI 200 //caratteri massimi per la recensione e descrizione
#define MAX_GENERI 5 //Numero massimo di generi inseribili
#define MAX_RECENSIONI 70 //Numero massimo di recensioni inseribili per ogni gioco, che sia un valore accettabile
#define MAX_PRODUCTION 100 // Numero massimo di copie distribuite, per evitare valori eccessivi
#define MAX_GIOCHI 50  // Giochi massimi per il catalogo nell'ordinamento, si presuppone non si vada oltre

/**
 * @brief Struttura per le recensioni dei videogiochi
 *
 */
typedef struct{
    int recensione_num; // 0-5, obbligatoria
    char recensione_scritta[MAX_CARATTERI_DESCRIZIONI]; //Facoltativa
}recensione_t;

/**
 * @brief Struttura che rappresenta un videogioco con le sue caratteristiche che sarà presente nel catalogo
 * L'implementazione di questa struttura permette di gestire le informazioni relative ai videogiochi, come il nome, l'editore, lo sviluppatore, la descrizione, l'anno di uscita, i generi, le recensioni e le copie vendute.
 * e si può trovare in parte nella struttura del file catalogo.dat, che contiene i videogiochi iniziali.
 */
//Struttura per i videogiochi
typedef struct {
    char nome[70]; // gioco col nome più lungo al mondo
    char editore[40]; // editore col nome più lungo al mondo
    char sviluppatore[40];
    char descrizione_breve_gioco[MAX_CARATTERI_DESCRIZIONI]; // facoltativa
    int anno_uscita;
    char genere[MAX_GENERI][MAX_CARATTERI_DESCRIZIONI];
    recensione_t recensione[MAX_RECENSIONI]; // array di recensioni, ogni gioco può avere più recensioni
    int copie_vendute; // Contatore degli acquisti
} videogame_t;

/**
 * @brief Funzioni per la gestione del Menu e delle operazioni per autentificarsi nel catalogo dei videogiochi
 *
 * L'impementazione di queste funzioni può essere trovato nel file Menu.c
 */
//Funzione per la gestione del menu
void MenuPrincipale();

/**
 * @brief Mostra il menu di amministrazione.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param check_admin Variabile che indica se l'utente è un admin (1) o un visitatore (0).
 */
void MenuAdmin(videogame_t videogame, char *nomeFile, short check_admin);

/**
 * @brief Mostra il menu visitatore.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param check_admin Variabile che indica se l'utente è un admin (1) o un visitatore (0).
 */
void MenuVisitatore(videogame_t videogame, char *nomeFile, short check_admin);

/**
 * @brief Gestisce l'autenticazione dell'admin.
 * @return 1 se l'autenticazione è andata a buon fine, 0 se si vuole continuare come visitatore, -1 se si vuole uscire dal programma.
 */
int AutenticazioneAdmin();

/**
 * @brief Funzioni per la gestione del catalogo dei videogiochi
 *
 * Queste funzioni permettono di cercare il catalogo dei videogiochi con i suo giochi
 * di default e di Ricerca i videogiochi in base al nome, sia per l'admin che per il visitatore.
 * Queste funzioni trovano la loro implementazione nel file Ricerca.c per quanto riguarda la ricerca dei videogiochi
 * e nel file CreazioneFile.c per quanto riguarda la scrittura del catalogo iniziale.
 *
 */
//Funzioni per la gestione del catalogo
/**
 * @brief Scrive il catalogo dei videogiochi.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 */
void ScriviCatalogo(char *nomeFile);

/**
 * @brief Ricerca un videogioco nel catalogo.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param check_admin Variabile che indica se l'utente è un admin (1) o un visitatore (0).
 */
void Ricerca(char *nomeFile, videogame_t videogame, short check_admin);

/**
 * @brief Visualizza l'intero catalogo dei videogiochi.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param videogame La struttura che rappresenta un videogioco (usata per iterazione).
 * @return void
 * @details Questa funzione è implementata nel file `Ordinamento.c`.
 */

/**
 * @brief Funzioni per la gestione della modifica, cancellazione, aggiunta e visualizzazione dei videogiochi da parte dell'admin, in base al
 * titolo del gioco inserito nella fase di Ricerca
 *
 * Queste funzioni vengono implementate nel file OperazioniAdmin.c, dove sono presenti le funzioni
 * eseguibili esclusivamente dall'admin per la gestione del catalogo dei videogiochi.
 */
//Funzioni per la gestione dei videogiochi da parte dell'admin
/**
 * @brief Modifica un gioco.
 * @param nomeFile il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param pos La posizione del videogioco nel catalogo, utile per le operazioni.
 */
void ModificaGioco(char *nomeFile, char* nome_ricerca, videogame_t videogame, short pos);

/**
 * @brief Cancella un gioco.
 * @param nomeFile il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param pos La posizione del videogioco nel catalogo, utile per le operazioni.
 */
void CancellaGioco(char *nomeFile, char* nome_ricerca, videogame_t videogame, short pos);

/**
 * @brief Aggiunge un gioco.
 * @param nomeFile il nome del file che contiene il catalogo dei videogiochi.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void AggiungiGioco(char *nomeFile, videogame_t videogame);

/**
 * @brief Funzioni per la gestione delle recensioni dei videogiochi da parte dell'utente
 *
 * Queste funzioni permettono di simulare un acquisto di un gioco, visualizzare le informazioni del gioco e aggiungere una recensione
 * in base al titolo del gioco inserito nella fase di Ricerca
 *
 * Trovano la loro implementazione nel file OperazioniUtente.c, dove sono presenti le funzioni
 * eseguibili esclusivamente dall'utente per la gestione del catalogo dei videogiochi
 *
 */
//Funzioni per la gestione dei videogiochi da parte dell'utente
/**
 * @brief Acquista un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param pos La posizione del videogioco nel catalogo, utile per le operazioni.
 */
void AcquistaGioco(char *nomeFile, char* nome_ricerca, videogame_t videogame, short pos);

/**
 * @brief Visualizza le informazioni di un videogioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void VisualizzaVideogioco(char *nomeFile, char* nome_ricerca, videogame_t videogame);

/**
 * @brief Aggiunge una recensione a un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @param pos La posizione del videogioco nel catalogo, utile per le operazioni.
 */
void AggiungiRecensione(char *nomeFile, char* nome_ricerca, videogame_t videogame, short pos);

/**
 * @brief Funzioni che possono eseguire entrambi sul catalogo dei videogiochi, sia da parte dell'admin che da parte dell'utente
 *
 * Queste funzioni permettono di visualizzare le recensioni di un gioco,
 * la possibilità di scegliere una statistica in base alle medie delle recensioni inserite e/o delle copie vendute
 * in base al titolo del gioco inserito nella fase di Ricerca
 *
 * Trovano la loro implementazione nel file OperazioniAU.c, dove sono presenti le funzioni eseguibili
 * da entrambi i ruoli per la gestione del catalogo dei videogiochi, queste stesse funzioni saranno richiamate in altre funzioni
 * come i due ordinamenti, la visualizzazione di un videogioco, l'acquisto di un videogioco e la gestione delle statistiche
 *
 */
//Funzioni per la gestione dei videogiochi per entrambi i ruoli
/**
 * @brief Visualizza le recensioni di un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void Visualizza_Recensione(char *nomeFile, char* nome_ricerca, videogame_t videogame);

/**
 * @brief Calcola la statistica delle recensioni di un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @return float
 */
float StatisticaRecensione(char *nomeFile, char* nome_ricerca, videogame_t videogame);

/**
 * @brief Calcola la statistica delle copie vendute di un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 * @return float
 */
float StatisticaCopieVendute(char *nomeFile, char* nome_ricerca, videogame_t videogame);

/**
 * @brief Visualizza le statistiche di un gioco.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param nome_ricerca Il nome del gioco da cercare nel catalogo.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void VisualizzaStatistiche(char *nomeFile, char* nome_ricerca, videogame_t videogame);

/**
 * @brief Funzioni per l'ordinamento del catalogo dei videogiochi in base alle copie vendute e alla media delle recensioni
 * in maniera decrescente, in modo da visualizzare i videogiochi più venduti e con le recensioni migliori fino a quelli meno venduti e con le recensioni peggiori.
 *
 * Trovano la loro implementazione nel file Ordinamento.c, dove sono presenti le funzioni
 * eseguibili da entrambi i ruoli per l'ordinamento del catalogo dei videogiochi in base alle copie vendute e alla media delle recensioni, espresse
 * nelle funzioni StatisticaRecensione e StatisticaCopieVendute.
 *
 */
//Funzioni per l'ordinamento
/**
 * @brief Ordina il catalogo per copie vendute.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void Ordinamento_copie_vendute(char *nomeFile, videogame_t videogame);

/**
 * @brief Ordina il catalogo per media recensioni.
 * @param nomeFile Il nome del file che contiene il catalogo dei videogiochi.
 * @param videogame La struttura che rappresenta un videogioco.
 */
void Ordinamento_media_recensioni(char *nomeFile, videogame_t videogame);

#endif // CATALOGOVIDEOGAME_H