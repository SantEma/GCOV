/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void Visualizza_Recensione(char *nomeFile, char *nome_ricerca, videogame_t videogioco){
    short recensione_generale=-1;                                      // Variabile per la recensione generale a -1 così da far valere lo 0 nello switch
    short pessimo=-1, insufficiente=-1, buono=-1, eccellente=-1;       // Contatori per le recensioni a -1 così da far valere lo 0 nello switch

    FILE *file=fopen(nomeFile, "rb");
    if (file!=NULL){
        printf("\nLe recensioni relative al gioco %s sono: ", nome_ricerca);
        for (short i=0; i<MAX_RECENSIONI; i++){
            if (videogioco.recensione[i].recensione_num!=-1){
                printf("\nRecensione %d e' %d", i+1, videogioco.recensione[i].recensione_num);
                if (videogioco.recensione[i].recensione_num==0){
                    printf("\nPessimo");
                    printf("\nRecensioni scritte: %s ", videogioco.recensione[i].recensione_scritta);
                    pessimo++;
                }
                else if (videogioco.recensione[i].recensione_num>0 && videogioco.recensione[i].recensione_num<=2){
                    printf("\nInsufficiente");
                    printf("\nRecensioni scritte: %s ", videogioco.recensione[i].recensione_scritta);
                    insufficiente++;
                }
                else if (videogioco.recensione[i].recensione_num>2 && videogioco.recensione[i].recensione_num<=4){
                    printf("\nBuono");
                    printf("\nRecensioni scritte: %s ", videogioco.recensione[i].recensione_scritta);
                    buono++;
                }
                else if (videogioco.recensione[i].recensione_num>4 && videogioco.recensione[i].recensione_num<=5){
                    printf("\nEccellente");
                    printf("\nRecensioni scritte: %s ", videogioco.recensione[i].recensione_scritta);
                    eccellente++;
                }
                else
                    printf("\nValore indesiderato per la recensione");
            }
        }

        // Stampa la recensione generale
        printf("\n-----------------\nRecensione generale: ");
        if (pessimo!=-1 || insufficiente || -1 || buono || -1 && eccellente || -1){
            if (pessimo>=insufficiente && pessimo>=buono && pessimo>=eccellente)
                recensione_generale=0; // Ponendo maggiore o uguale, sarà visualizzata comunque una recensione, se fosse solo maggiore si creerebbe un conflitto
            else if (insufficiente>=pessimo && insufficiente>=buono && insufficiente>=eccellente)
                recensione_generale=1;
            else if (buono>=pessimo && buono>=insufficiente && buono>=eccellente)
                recensione_generale=2;
            else if (eccellente>pessimo && eccellente>insufficiente && eccellente>buono)
                recensione_generale=3;
            else
                printf("\nValore indesiderato per la recensione generale");
        }
        switch (recensione_generale){
        case 0:
            printf("Pessima");
            break;
        case 1:
            printf("Insufficiente");
            break;
        case 2:
            printf("Buona");
            break;
        case 3:
            printf("Eccellente");
            break;
        default:
            printf("Recensione generale non presente attualmente");
            break;
        }
        fclose(file);
    }

    else
        printf("\nErrore nell'apertura del file per visualizzare la recensione\n");
}

float StatisticaRecensione(char *nomeFile, char *nome_ricerca ,videogame_t videogioco){
    float media=0.0;
    short count=0; // Contatore per le recensioni valide

    FILE *file=fopen(nomeFile, "rb");
    if(file!=NULL){
        for(short i=0;i<MAX_RECENSIONI;i++){
            if(videogioco.recensione[i].recensione_num!=-1){
                count++;
                media+=videogioco.recensione[i].recensione_num;
            }
        }
        media=media/count; // Calcola la media delle recensioni
        fclose(file);
        return media;
    }
    else printf("\nErrore nell'apertura del file per il calcolo della media delle recensioni\n");

}
float StatisticaCopieVendute(char *nomeFile, char *nome_ricerca, videogame_t videogioco){
    float media=0.0;

    FILE *file=fopen(nomeFile, "rb");
    if(file!=NULL){
        if(videogioco.copie_vendute>=0) media=(float)videogioco.copie_vendute/ MAX_PRODUCTION; // Calcola la media delle copie centinaia in migliaia di copie distribuite ed eseguo il cast temporaneo per poter inserire un float all'interno della variabile media
        else{
            printf("\nIl gioco %s non ha copie vendute registrate.\n", nome_ricerca);
            return 0.0; // Se non ci sono copie vendute, ritorna 0.0
        }
        fclose(file);
        return media;
    }
    else printf("\nErrore nell'apertura del file per il calcolo della media delle recensioni\n");
}