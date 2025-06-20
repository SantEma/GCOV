/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

// Fase di -> Ricerca
/* La ricerca del videogame si divide in due tipi:
 * l'admin potrà ricercare un videogame solo per effettuare 3 operazioni madri:
 * MODIFICA(tra cui aggiunta), CANCELLAZIONE, VISUALIZZARE RECENSIONE
 *
 * L'utente invece può solamente ricercare per visualizzare le informazioni di un gioco
 * e aggiungere una recensione ed acquistare il gioco.
 */

void Ricerca(char *nomeFile, videogame_t videogioco, short check_admin){
    char nome_ricerca[70];
    short check_name = 0; // flag per verificare se il nome del gioco è stato trovato
    short pos = -1;       // Variabile per la posizione del gioco in cui eseguire le operazioni
    short found_pos = 0;  // Variabile per tenere traccia della posizione del gioco

    FILE *file = fopen(nomeFile, "rb");
    if (file != NULL){
        printf("\n-------------------------");
        printf("\nInserire il nome del gioco da ricercare: ");
        fgets(nome_ricerca, sizeof(nome_ricerca), stdin);
        nome_ricerca[strcspn(nome_ricerca, "\n")] = 0; // Rimuove il newline finale

        // Da finire con la ricerca in sottostringhe e di upperCase e lowercase e sottostringhe

        // ciclo per la ricerca del gioco
        while (fread(&videogioco, sizeof(videogame_t), 1, file) == 1){
            if (strcmp(videogioco.nome, nome_ricerca) == 0){
                check_name = 1; // se il gioco è stato trovato
                printf("\nGioco trovato:\n");
                pos = found_pos;
                break;
            }
            found_pos++;
        }

        if (check_name){
            if (check_admin){
                // Scelta dell'operazione da eseguire con richiamo alla sua funzione - Admin
                printf("\nScegli l'operazione da eseguire:\n");
                printf("1 - Modifica un campo del gioco\n2 - Cancella il gioco\n3 - Aggiungi un gioco dopo questo\n4 - Visualizza recensione del gioco\n5 - Statistica\nScelta:");
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
                        char scelta_statistica;
                        float media_recensione = 0.0;
                        float mcopie_vendute = 0.0;

                        printf("\nVisualizzare le statistiche del gioco in base alle copie vendute o le recensione? (c/r): \n");
                        do{
                            scanf(" %c", &scelta_statistica);
                            if(scelta_statistica == 'r' || scelta_statistica == 'R'){
                                media_recensione=StatisticaRecensione(nomeFile, nome_ricerca, videogioco);
                                printf("\nMedia delle recensioni del gioco %s: %.2f\n",nome_ricerca, media_recensione);
                            }
                            else if(scelta_statistica == 'c' || scelta_statistica == 'C'){
                                mcopie_vendute=StatisticaCopieVendute(nomeFile, nome_ricerca, videogioco);
                                if(mcopie_vendute != 0.0) printf("\nMedia delle copie vendute del gioco %s: \n", nome_ricerca, mcopie_vendute);
                                else printf("\nIl gioco %s non ha copie vendute registrate.\n", nome_ricerca);
                            }
                            else printf("\nScelta non valida, Rinserire: \n");
                        }while(scelta_statistica != 'c' && scelta_statistica != 'C' && scelta_statistica != 'r' && scelta_statistica != 'R');
                        break;

                    default:
                        printf("\nOperazione non valida. Reinserire valore corretto\n");
                        break;
                    }
                } while (scelta_operazioneFile < 1 || scelta_operazioneFile > 5); // Assicura che la scelta sia tra 1 e 4
            }

            else{
                // Scelta dell'operazione da eseguire con richiamo alla sua funzione - Utente
                printf("\nScegli l'operazione da eseguire:\n");
                printf("1 - Visualizza informazioni del gioco\n2 - Acquista un gioco\n3 - Aggiungi una recensione al gioco\n4 - Statistica\nScelta:");
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
                        char scelta_statistica;
                        float media_recensione = 0.0;
                        float mcopie_vendute = 0.0;

                        printf("\nVisualizzare le statistiche del gioco in base alle copie vendute o le recensione? (c/r): \n");
                        do{
                            scanf(" %c", &scelta_statistica);
                            if(scelta_statistica == 'r' || scelta_statistica == 'R'){
                                media_recensione=StatisticaRecensione(nomeFile, nome_ricerca, videogioco);
                                printf("\nMedia delle recensioni del gioco %s: %.2f\n",nome_ricerca, media_recensione);
                            }
                            else if(scelta_statistica == 'c' || scelta_statistica == 'C'){
                                mcopie_vendute=StatisticaCopieVendute(nomeFile, nome_ricerca, videogioco);
                                if(mcopie_vendute != 0.0) printf("\nMedia delle copie vendute del gioco %s: %.2f \n", nome_ricerca, mcopie_vendute);
                                else printf("\nIl gioco %s non ha copie vendute registrate.\n", nome_ricerca);
                            }
                            else printf("\nScelta non valida, Rinserire: \n");
                        }while(scelta_statistica != 'c' && scelta_statistica != 'C' && scelta_statistica != 'r' && scelta_statistica != 'R');
                        break;

                    default:
                        printf("\nOperazione non valida. Reinserire valore corretto\n");
                        break;
                    }
                } while (scelta_operazioneFile < 1 || scelta_operazioneFile > 4); // Assicura che la scelta sia tra 1 e 3
            }

            fclose(file);
        }

        if (check_name == 0){
            printf("\nGioco non trovato nel catalogo.");
        }
    }
    else
        printf("\nErrore nell'apertura del file");
}
