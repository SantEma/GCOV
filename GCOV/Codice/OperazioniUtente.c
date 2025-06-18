/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void VisualizzaVideogioco(char *nomeFile, videogame_t videogioco, char* nome_ricerca){
    FILE *file=fopen(nomeFile, "rb");
    if(file!=NULL){
        // Ricerca del gioco da visualizzare
        while(fread(&videogioco.nome, sizeof(videogame_t), 1, file) == 1){
            if(strcmp(videogioco.nome, nome_ricerca) == 0){
                printf("\nNome: %s", videogioco.nome);
                printf("\nEditore: %s", videogioco.editore);
                printf("\nSviluppatore: %s", videogioco.sviluppatore);
                printf("\nDescrizione: %s", videogioco.descrizione_breve_gioco);
                printf("\nAnno di uscita: %d", videogioco.anno_uscita);
                printf("\nGeneri: ");
                for(short i=0; i<MAX_GENERI && videogioco.genere[i][0] != '\0'; i++){ //videogioco.genere[i][0] != '\0' serve per evitare di leggere generi vuoti fermandosi all'ultimo che non sia ""
                    printf("%s ", videogioco.genere[i]);
                }
                Visualizza_Recensione(nomeFile, videogioco, nome_ricerca);
                printf("\nCopie vendute: %d\n", videogioco.copie_vendute);
            }
        }
        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per la visualizzazione del gioco.\n");
}

void AggiungiRecensione(char *nomeFile, videogame_t videogioco, char* nome_ricerca){
    char scelta_recensionescritt;
    int pos=-1; //Variabile per la posizione del gioco da modificare
    int found_pos=0; // Variabile per tenere traccia della posizione del gioco nel file

    FILE *file=fopen(nomeFile, "rb+");
    if(file!=NULL){
        while(fread(&videogioco, sizeof(videogame_t), 1, file) == 1){
            if(strcmp(videogioco.nome, nome_ricerca) == 0){
                pos = found_pos;
            }
            found_pos++;
        }
            
        for(short i=0; i<MAX_RECENSIONI; i++){
            if(videogioco.recensione[i].recensione_num == -1){ // Trova la prima recensione vuota
                printf("\nInserisci la valutazione (0-5): ");
                scanf("%d", &videogioco.recensione[i].recensione_num);
                while (getchar() != '\n'); // Svuota il buffer
                if(videogioco.recensione[i].recensione_num < 0 || videogioco.recensione[i].recensione_num > 5){
                    printf("\nValutazione non valida, rinserirla, deve essere compresa tra 0 e 5.\n");
                    i--; // Ritorna indietro per ripetere l'inserimento della recensione
                }

                printf("Vuoi inserire una recensione scritta? (s/n): ");
                do{
                    scanf("%c", &scelta_recensionescritt);
                    if(scelta_recensionescritt == 's' || scelta_recensionescritt == 'S'){
                        printf("Inserisci la recensione scritta (max %d caratteri): ", MAX_CARATTERI_DESCRIZIONI);
                        fgets(videogioco.recensione[i].recensione_scritta, sizeof(videogioco.recensione[i].recensione_scritta), stdin);
                        videogioco.recensione[i].recensione_scritta[strcspn(videogioco.recensione[i].recensione_scritta, "\n")] = 0; // Rimuove il newline finale
                    }
                    else if(scelta_recensionescritt == 'n' || scelta_recensionescritt == 'N'){
                        videogioco.recensione[i].recensione_scritta[0] = '\0'; // Imposta la recensione scritta come vuota
                    }
                    else printf("\nScelta non valida, rinserire: \n");
                }while(scelta_recensionescritt != 's' && scelta_recensionescritt != 'S' && scelta_recensionescritt != 'n' && scelta_recensionescritt != 'N');
            }
            else printf("Sono presenti gia' abbastanza recensioni per questo gioco.\n");
        }
        // Aggiorna il file con la nuova recensione
        fseek(file, pos * sizeof(videogame_t), SEEK_SET); // Torna alla posizione del gioco
        if(fwrite(&videogioco, sizeof(videogame_t), 1, file) != 1) printf("\nErrore nella scrittura della recensione nel file.\n");            
        else printf("\nRecensione aggiunta con successo!\n");

        fseek(file,0,SEEK_SET);

        //Test
        printf("\nQueste sono le recensioni del gioco con questa nuova aggiunta '%s':\n", videogioco.nome);
        Visualizza_Recensione(nomeFile, videogioco, nome_ricerca);
        
        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per l'aggiunta della recensione.\n");
}
