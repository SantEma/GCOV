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
    else printf("\nErrore nell'apertura del file per la visualizzazione del gioco.");
}

