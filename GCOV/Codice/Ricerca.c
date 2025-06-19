/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

 //Fase di -> Ricerca
        /* La ricerca del videogame si divide in due tipi:
        * l'admin potrà ricercare un videogame solo per effettuare 3 operazioni madri:
        * MODIFICA(tra cui aggiunta), CANCELLAZIONE, VISUALIZZARE RECENSIONE
        * 
        * L'utente invece può solamente ricercare per visualizzare le informazioni di un gioco
        * e aggiungere una recensione ed acquistare il gioco.
        */ 

void Ricerca(char *nomeFile, videogame_t videogioco, short check_admin){
    char nome_ricerca[70];
    short check_name=0; //flag per verificare se il nome del gioco è stato trovato
    FILE *file = fopen(nomeFile, "rb");
    if (file != NULL) {
        printf("\n-------------------------");
        printf("\nInserire il nome del gioco da ricercare: ");
        fgets(nome_ricerca, sizeof(nome_ricerca), stdin);
        nome_ricerca[strcspn(nome_ricerca, "\n")] = 0; // Rimuove il newline finale

        //Da finire con la ricerca in sottostringhe e di upperCase e lowercase e sottostringhe

        //ciclo per la ricerca del gioco
        while(fread(&videogioco,sizeof(videogame_t), 1, file) == 1){
            if(strcmp(videogioco.nome, nome_ricerca) == 0){
                check_name=1; //se il gioco è stato trovato
                printf("\nGioco trovato:\n");
                
                if(check_admin){
                    //Scelta dell'operazione da eseguire con richiamo alla sua funzione - Admin
                    printf("\nScegli l'operazione da eseguire:\n");
                    printf("1 - Modifica un campo del gioco\n2 - Cancella il gioco\n3 - Aggiungi un gioco dopo questo\n4 - Visualizza recensione del gioco\nScelta:");
                    short scelta_operazioneFile;
                    
                    do{
                        scanf("%hd", &scelta_operazioneFile);
                        switch (scelta_operazioneFile){
                            case 1:
                                ModificaGioco(nomeFile, videogioco, nome_ricerca);
                                break;
                
                            case 2:
                                CancellaGioco(nomeFile, videogioco, nome_ricerca);
                                break;

                            case 3:
                                AggiungiGioco(nomeFile, videogioco);
                                break;
                        
                            case 4:
                                Visualizza_Recensione(nomeFile,videogioco, nome_ricerca);
                                break;
                        
                            default:
                                printf("\nOperazione non valida. Reinserire valore corretto\n");
                                break;
                        }
                    } while(scelta_operazioneFile < 1 || scelta_operazioneFile > 4); // Assicura che la scelta sia tra 1 e 4
                }

                else{
                    //Scelta dell'operazione da eseguire con richiamo alla sua funzione - Utente
                    printf("\nScegli l'operazione da eseguire:\n");
                    printf("1 - Visualizza informazioni del gioco\n2 - Acquista un gioco\n3 - Aggiungi una recensione al gioco\nScelta:");
                    short scelta_operazioneFile;
                    
                    do{
                        scanf("%hd", &scelta_operazioneFile);
                        switch (scelta_operazioneFile){
                            case 1:
                                VisualizzaVideogioco(nomeFile, videogioco, nome_ricerca);
                                break;
                
                            case 2:
                                AcquistaGioco(nomeFile, videogioco, nome_ricerca);
                                break;

                            case 3:
                                AggiungiRecensione(nomeFile, videogioco, nome_ricerca);
                                break;
                        
                            default:
                                printf("\nOperazione non valida. Reinserire valore corretto\n");
                                break;
                        }
                    } while(scelta_operazioneFile < 1 || scelta_operazioneFile > 3); // Assicura che la scelta sia tra 1 e 3
                }
            }
        }
        fclose(file);
        if(check_name == 0){
            printf("\nGioco non trovato nel catalogo.");
        }
    }
    else printf("\nErrore nell'apertura del file");
}
