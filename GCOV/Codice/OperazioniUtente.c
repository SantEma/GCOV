/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void VisualizzaVideogioco(char *nomeFile, char* nome_ricerca, videogame_t videogioco, short pos ){
    FILE *file=fopen(nomeFile, "rb");
    if(file!=NULL){
        // Ricerca del gioco da visualizzare
        printf("\nNome: %s", videogioco.nome);
        printf("\nEditore: %s", videogioco.editore);
        printf("\nSviluppatore: %s", videogioco.sviluppatore);
        printf("\nDescrizione: %s", videogioco.descrizione_breve_gioco);
        printf("\nAnno di uscita: %d", videogioco.anno_uscita);
        printf("\nGeneri: ");
        for(short i=0; i<MAX_GENERI && videogioco.genere[i][0] != '\0'; i++){ //videogioco.genere[i][0] != '\0' serve per evitare di leggere generi vuoti fermandosi all'ultimo che non sia ""
            printf("%s ", videogioco.genere[i]);
        }
        Visualizza_Recensione(nomeFile, nome_ricerca, videogioco, pos);
        printf("\nCopie vendute: %d\n", videogioco.copie_vendute);
        
        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per la visualizzazione del gioco.\n");
}

void AggiungiRecensione(char *nomeFile, char* nome_ricerca, videogame_t videogioco, short pos){
    char scelta_recensionescritt;
    short recensione_impostata=0; // Flag per verificare se è stata impostata una recensione

    FILE *file=fopen(nomeFile, "rb+");
    if(file!=NULL){
        for(short i=0; i<MAX_RECENSIONI; i++){
            if(videogioco.recensione[i].recensione_num == -1){ // Trova la prima recensione vuota
                printf("\nInserisci la valutazione (0-5): ");
                do{
                    scanf("%d", &videogioco.recensione[i].recensione_num);
                    while (getchar() != '\n'); // Svuota il buffer
                    printf("\nValutazione inserita: %d", videogioco.recensione[i].recensione_num);
                    if(videogioco.recensione[i].recensione_num < 0 || videogioco.recensione[i].recensione_num > 5) printf("\nValutazione non valida, rinserirla, deve essere compresa tra 0 e 5.\n");
                }while(videogioco.recensione[i].recensione_num < 0 || videogioco.recensione[i].recensione_num > 5);

                printf("Vuoi inserire una recensione scritta? (s/n): ");
                do{
                    scanf("%c", &scelta_recensionescritt);
                    while (getchar() != '\n'); // Svuota il buffer
                    if(scelta_recensionescritt == 's' || scelta_recensionescritt == 'S'){
                        printf("Inserisci la recensione scritta (max %d caratteri): ", MAX_CARATTERI_DESCRIZIONI-1);
                        fgets(videogioco.recensione[i].recensione_scritta, sizeof(videogioco.recensione[i].recensione_scritta), stdin);
                        videogioco.recensione[i].recensione_scritta[strcspn(videogioco.recensione[i].recensione_scritta, "\n")] = 0; // Rimuove il newline finale
                    }
                    else if(scelta_recensionescritt == 'n' || scelta_recensionescritt == 'N'){
                        videogioco.recensione[i].recensione_scritta[0] = '\0'; // Imposta la recensione scritta come vuota
                    }
                    else printf("\nScelta non valida, rinserire: \n");
                }while(scelta_recensionescritt != 's' && scelta_recensionescritt != 'S' && scelta_recensionescritt != 'n' && scelta_recensionescritt != 'N');
                break; // Esce dalla funzione se non ci sono più spazi per le recensioni
            }
            recensione_impostata=1;
        }
        if(recensione_impostata == 0) printf("\nNon è possibile aggiungere altre recensioni, il massimo è %d.\n", MAX_RECENSIONI);
        
        // Aggiorna il file con la nuova recensione
        fseek(file, pos * sizeof(videogame_t), SEEK_SET); // Torna alla posizione del gioco
        if(fwrite(&videogioco, sizeof(videogame_t), 1, file) != 1) printf("\nErrore nella scrittura della recensione nel file.\n");            
        else printf("\nRecensione aggiunta con successo!\n");
        fseek(file,0,SEEK_SET);

        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per l'aggiunta della recensione.\n");
}

void AcquistaGioco(char *nomeFile, char* nome_ricerca, videogame_t videogioco,short pos){
    short gioco_acquistato = 0; // Flag per indicare se il gioco è stato acquistato

    FILE *file=fopen(nomeFile, "rb+");
    if(file!=NULL){
        videogioco.copie_vendute++;
        gioco_acquistato = 1;

        //Aggiornamento contatore delle copie vendute
        if(gioco_acquistato){
            fseek(file,pos*sizeof(videogame_t), SEEK_SET); // Torna alla posizione del gioco
            if(fwrite(&videogioco, sizeof(videogame_t), 1, file) != 1) printf("\nErrore nella scrittura del file per l'acquisto del gioco.\n");
            else printf("\nIl gioco %s e' stato acquistato con successo!\n", videogioco.nome);
            
            //Richiesta di recensione
            printf("\nVuoi aggiungere una recensione al gioco appena acquistato? (s/n): ");
            char scelta_recensione;
            scanf(" %c", &scelta_recensione);
            if(scelta_recensione == 's' || scelta_recensione == 'S'){
                AggiungiRecensione(nomeFile, nome_ricerca,videogioco, pos);
            }
            else if(scelta_recensione == 'n' || scelta_recensione == 'N'){
                printf("\nRecensione non aggiunta.\n");
            }
            else printf("\nScelta non valida, recensione non aggiunta.\n");

        }
        else printf("\nGioco non disponibile nel catalogo.\n");

        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per l'acquisto del gioco.\n");
}
