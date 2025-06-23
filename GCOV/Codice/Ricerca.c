/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "CatalogoVideogame.h"

// Fase di Ricerca
/* La ricerca del videogame si divide in due tipi:
 * l'admin potrà ricercare un videogame solo per effettuare 3 operazioni madri:
 * MODIFICA(tra cui aggiunta), CANCELLAZIONE, VISUALIZZARE RECENSIONE
 *
 * L'utente invece può solamente ricercare per visualizzare le informazioni di un gioco
 * e aggiungere una recensione ed acquistare il gioco.
 */

void Ricerca(char *nomeFile, videogame_t videogioco, short check_admin){
    char nome_ricerca[70];
    short check_name=0; // Flag per verificare se il nome del gioco è stato trovato
    short pos=-1;       // Variabile per la posizione del gioco in cui eseguire le operazioni
    short found_pos=0;  // Variabile per tenere traccia della posizione del gioco

    FILE *file=fopen(nomeFile, "rb");
    if (file!=NULL){
        printf("\n-------------------------");
        printf("\nInserire il nome del gioco da ricercare: ");
        fgets(nome_ricerca, sizeof(nome_ricerca), stdin);
        nome_ricerca[strcspn(nome_ricerca, "\n")]=0; // Rimuove il newline finale

        // ciclo per la ricerca del gioco
        while (fread(&videogioco, sizeof(videogame_t), 1, file)==1){
            if (strcmp(videogioco.nome, nome_ricerca)==0){
                check_name=1; // se il gioco è stato trovato
                printf("\nGioco trovato:\n");
                pos=found_pos;
                break;
            }
            found_pos++;
        }

        if (check_name){
            if (check_admin){
                // Scelta dell'operazione da eseguire con richiamo alla sua funzione - Admin
                printf("\nScegli l'operazione da eseguire:\n");
                printf("1)Modifica un campo del gioco\n2)Cancella il gioco\n3)Aggiungi un gioco dopo questo\n4)Visualizza recensione del gioco\n5)Statistica\nScelta:");
                short scelta_operazioneFile;

                do{
                    scanf("%hd", &scelta_operazioneFile);
                    switch (scelta_operazioneFile){
                    case 1:
                        ModificaGioco(nomeFile, nome_ricerca, videogioco, pos);
                        break;

                    case 2:
                        CancellaGioco(nomeFile, nome_ricerca, videogioco, pos);
                        break;

                    case 3:
                        AggiungiGioco(nomeFile, videogioco);
                        break;

                    case 4:
                        Visualizza_Recensione(nomeFile, nome_ricerca, videogioco);
                        break;

                    case 5:
                        VisualizzaStatistiche(nomeFile, nome_ricerca, videogioco);
                        break;

                    default:
                        printf("\nOperazione non valida. Reinserire valore corretto\n");
                        break;
                    }
                } while (scelta_operazioneFile<1||scelta_operazioneFile>5); // Assicura che la scelta sia tra 1 e 4
            }

            else{
                // Scelta dell'operazione da eseguire con richiamo alla sua funzione - Utente
                printf("\nScegli l'operazione da eseguire:\n");
                printf("1)Visualizza informazioni del gioco\n2)Acquista un gioco\n3)Aggiungi una recensione al gioco\n4)Statistica\nScelta:");
                short scelta_operazioneFile;

                do{
                    scanf("%hd", &scelta_operazioneFile);
                    switch (scelta_operazioneFile){
                    case 1:
                        VisualizzaVideogioco(nomeFile, nome_ricerca, videogioco);
                        break;

                    case 2:
                        AcquistaGioco(nomeFile, nome_ricerca, videogioco, pos);
                        break;

                    case 3:
                        AggiungiRecensione(nomeFile, nome_ricerca, videogioco, pos);
                        break;

                    case 4:
                        VisualizzaStatistiche(nomeFile, nome_ricerca, videogioco);
                        break;

                    default:
                        printf("\nOperazione non valida. Reinserire valore corretto\n");
                        break;

                    }
                } while (scelta_operazioneFile<1||scelta_operazioneFile>4); // Assicura che la scelta sia tra 1 e 3
            }

            fclose(file);
        }

        if (check_name == 0) {
            // Se non viene trovata una corrispondenza esatta, si passa alla ricerca per sottostringa.
            // Il file originale viene chiuso per evitare resource leak.
            fclose(file);

            short scelta;
            short trovati = 0;
            videogame_t risultati[MAX_GIOCHI];

            printf("\nGioco non trovato nel catalogo, potrebbe essere inesistente o con nome errato, ecco le alternative trovate.");
            while(getchar()!='\n');

            FILE *file_sub = fopen(nomeFile, "rb");
            if (file_sub != NULL) {
                printf("\nVideogiochi trovati con la sottostringa '%s':\n", nome_ricerca);
                while (fread(&videogioco, sizeof(videogame_t), 1, file_sub) == 1 && trovati < MAX_GIOCHI) {
                    if (strstr(videogioco.nome, nome_ricerca) != NULL) {
                        printf("- %s\n", videogioco.nome);
                        risultati[trovati] = videogioco;
                        trovati++;
                    }
                }

                if (trovati > 0) {
                    printf("\nSono stati trovati %hd giochi con la sottostringa '%s'.\n", trovati, nome_ricerca);
                    do {
                        printf("\nScegli il gioco da visualizzare (0-%hd): ", trovati - 1);
                        scanf("%hd", &scelta);

                        if (scelta >= 0 && scelta < trovati) {
                            videogioco = risultati[scelta];
                            check_name = 1;
                            strcpy(nome_ricerca, videogioco.nome);

                            fclose(file_sub);
                            file_sub = fopen(nomeFile, "rb");

                            if (file_sub != NULL) {
                                short indice = 0;
                                videogame_t tmp;
                                while (fread(&tmp, sizeof(videogame_t), 1, file_sub) == 1) {
                                    if (strcmp(tmp.nome, nome_ricerca) == 0) {
                                        pos = indice;
                                        break;
                                    }
                                    indice++;
                                }
                            }

                        } else {
                            printf("\nScelta non valida. Reinserire un numero tra 0 e %hd.\n", trovati - 1);
                        }
                    } while (scelta < 0 || scelta >= trovati);
                }

                if (file_sub != NULL) {
                    fclose(file_sub);
                }
            }
        }
    }
    else printf("\nErrore nell'apertura del file");
}