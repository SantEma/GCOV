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
        * e aggiungere una recensione
        */ 

void RicercaAdmin(char *nomeFile, videogame_t videogioco){
    char nome_ricerca[70];
    short check_name=0; //flag per verificare se il nome del gioco è stato trovato
    FILE *file = fopen(nomeFile, "rb");
    if (file != NULL) {
        printf("\nInserire il nome del gioco da ricercare: ");
        fgets(nome_ricerca, sizeof(nome_ricerca), stdin);
        nome_ricerca[strcspn(nome_ricerca, "\n")] = 0; // Rimuove il newline finale
        videogioco.nome[strcspn(videogioco.nome, "\n")] = 0;
        //strcpy(nome_ricerca, "The Legend of Zelda: Breath of the Wild"); //per testare la ricerca di un gioco specifico
        

        //ciclo per la ricerca del gioco
        while(fread(&videogioco,sizeof(videogame_t), 1, file) == 1){
            if(strcmp(videogioco.nome, nome_ricerca) == 0){
                check_name=1; //se il gioco è stato trovato
                printf("\nGioco trovato:\n");
                printf("Nome: %s\n", videogioco.nome);
                printf("Editore: %s\n", videogioco.editore);
                printf("Sviluppatore: %s\n", videogioco.sviluppatore);
                printf("Descrizione: %s\n", videogioco.descrizione_breve_gioco);
                printf("Anno di uscita: %d\n", videogioco.anno_uscita);
                printf("Genere: %s\n", videogioco.genere);
                printf("Recensione: %d\n", videogioco.recensione);

                printf("\nFinito test per vedere se il catalogo viene letto");
            }
        }
        fclose(file);
        if(check_name == 0){
            printf("\nGioco non trovato nel catalogo.");
        }
    }
    else printf("\nErrore nell'apertura del file");
}

void RicercaVisitatore(char *nomeFile, videogame_t videogioco){
    
}