/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void Visualizza_Recensione(char *nomeFile, videogame_t videogioco, char *nome_ricerca){
    short recensione_generale=0; //Variabile per la recensione generale
    short pessimo=0, insufficiente=0, buono=0, eccellente=0; //Contatori per le recensioni

    FILE *file=fopen(nomeFile,"rb");
    if(file!=NULL){
        while(fread(&videogioco,sizeof(videogame_t),1,file)==1){
            if(strcmp(videogioco.nome,nome_ricerca)==0){
                printf("\nLe recensioni relative al gioco %s sono: ", nome_ricerca);

                for(short i=0; i<MAX_RECENSIONI; i++){
                    if(videogioco.recensione[i].recensione_num==-1) break; // Salta le recensioni non inserite
                    if(videogioco.recensione[i].recensione_num==0){
                        printf("\nPessimo");
                        printf("\nRecensioni scritte: %s ",videogioco.recensione[i].recensione_scritta);
                        pessimo++;
                    }
                    else if(videogioco.recensione[i].recensione_num>0 && videogioco.recensione[i].recensione_num<=2){
                        printf("\nInsufficiente");
                        printf("\nRecensioni scritte: %s ",videogioco.recensione[i].recensione_scritta);
                        insufficiente++;
                    }
                    else if(videogioco.recensione[i].recensione_num>2 && videogioco.recensione[i].recensione_num<=4){
                        printf("\nBuono");
                        printf("\nRecensioni scritte: %s ",videogioco.recensione[i].recensione_scritta);
                        buono++;
                    }
                    else if(videogioco.recensione[i].recensione_num>4 && videogioco.recensione[i].recensione_num<=5){
                        printf("\nEccellente");
                        printf("\nRecensioni scritte: %s ",videogioco.recensione[i].recensione_scritta);
                        eccellente++;
                    }
                    else printf("\nValore indesiderato per la recensione"); 
                }

                // Stampa la recensione generale
                printf("\n-----------------\nRecensione generale: ");
                if(pessimo>=insufficiente && pessimo>=buono && pessimo>=eccellente) recensione_generale=0; //Ponendo maggiore o uguale, sarà visualizzata comunque una recensione, se fosse solo maggiore si creerebbe un conflitto
                else if(insufficiente>=pessimo && insufficiente>=buono && insufficiente>=eccellente) recensione_generale=1;
                else if(buono>=pessimo && buono>=insufficiente && buono>=eccellente) recensione_generale=2;
                else if(eccellente>=pessimo && eccellente>=insufficiente && eccellente>=buono) recensione_generale=3;
                else printf("\nValore indesiderato per la recensione generale");
                switch (recensione_generale) {
                    case 0:
                        printf("\nPessima");
                        break;
                    case 1:
                        printf("\nInsufficiente");
                        break;
                    case 2:
                        printf("\nBuona");
                        break;
                    case 3:
                        printf("\nEccellente");
                        break;
                    default:
                        printf("\nRecensione generale non valida");
                        break;
                }
            }
        }
        
        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per visualizzare la recensione\n");
}