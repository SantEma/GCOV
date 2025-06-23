/**
 * @file Ordinamento.c
 * @author Andrea Milo
 * @brief Funzioni per l'ordinamento dei videogiochi nel catalogo
 * @version 0.1
 * @date 2025-05-22
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void Ordinamento_copie_vendute(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");
    
    if (file!=NULL){
        // Array per i giochi da riordinare
        videogame_t catalogo[MAX_GIOCHI];

        // Conta il numero di giochi nel file
        int num_giochi=0;
        while (fread(&videogioco, sizeof(videogame_t), 1, file)==1){
            num_giochi++;
        }

        if (num_giochi==0){
            printf("\nNessun gioco presente nel catalogo\n");
            return;
        }
        else if (num_giochi>MAX_GIOCHI){
            printf("\nTroppi giochi nel catalogo (massimo %d)\n", MAX_GIOCHI);
            return;
        }

        for (int i=0;i<num_giochi;i++){
            fread(&catalogo[i], sizeof(videogame_t), 1, file);
        }
        fclose(file);

        // Shell sort per copie vendute, in ordine decrescente
        int intervallo=num_giochi/2;
        while (intervallo>0){
            for (int i=intervallo; i<num_giochi; i++){
                videogame_t temp=catalogo[i];
                int j=i;
                while (j>=intervallo && catalogo[j-intervallo].copie_vendute<temp.copie_vendute){
                    catalogo[j]=catalogo[j-intervallo];
                    j-=intervallo;
                }
                catalogo[j]=temp;
            }
            intervallo/=2;
        }

        // Output finale ordinato con statistiche integrate
        printf("\n---CLASSIFICA GIOCHI PER COPIE VENDUTE---\n");
        for(int i=0; i<num_giochi; i++){
            printf("\n%s", catalogo[i].nome);
            printf("\nCopie vendute: %d", catalogo[i].copie_vendute);
            printf("\nEditore: %s", catalogo[i].editore);
            printf("\nDescrizione : %s", catalogo[i].descrizione_breve_gioco);
            printf("\nSviluppatore: %s", catalogo[i].sviluppatore);
            printf("\nAnno uscita: %d", catalogo[i].anno_uscita);
            for(short j=0; j<MAX_GENERI && catalogo[i].genere[j][0]!='\0'; j++){ //videogioco.genere[i][0] != '\0' serve per evitare di leggere generi vuoti fermandosi all'ultimo che non sia ""
                printf("%s ", catalogo[i].genere[j]);
            }
            for (short x=0; x<MAX_RECENSIONI; x++){
            if (catalogo[i].recensione[x].recensione_num!=-1){
                printf("\nRecensione %d e' %d", i+1, catalogo[i].recensione[x].recensione_num);
                if (catalogo[i].recensione[x].recensione_num==0){
                    printf("\nPessimo");
                    printf("\nRecensioni scritte: %s ", catalogo[i].recensione[x].recensione_scritta);
                }
                else if (catalogo[i].recensione[x].recensione_num>0 && catalogo[i].recensione[x].recensione_num<=2){
                    printf("\nInsufficiente");
                    printf("\nRecensioni scritte: %s ", catalogo[i].recensione[x].recensione_scritta);
                }
                else if (catalogo[i].recensione[x].recensione_num>2 && catalogo[i].recensione[x].recensione_num<=4){
                    printf("\nBuono");
                    printf("\nRecensioni scritte: %s ", catalogo[i].recensione[x].recensione_scritta);
                }
                else if (catalogo[i].recensione[x].recensione_num>4 && catalogo[i].recensione[x].recensione_num<=5){
                    printf("\nEccellente");
                    printf("\nRecensioni scritte: %s ", catalogo[i].recensione[x].recensione_scritta);
                }
            }
        }
            printf("-------------------------------------"); 
        } 
             
        fclose(file);
    }
    else{
        printf("\nErrore nell'apertura del file per l'ordinamento\n");
    }
}


void Ordinamento_media_recensioni(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");
    if(file==NULL){
        printf("\nErrore nell'apertura del file per l'ordinamento per statistiche\n");
        return;
    }

    //Array per i giochi e le medie valutazioni
    videogame_t catalogo[MAX_GIOCHI];
    float medie_recensioni[MAX_GIOCHI];
    
    //Conta il numero di giochi nel file
    int num_giochi=0;
    while(fread(&videogioco, sizeof(videogame_t), 1, file)==1){
        num_giochi++;
    }
    fclose(file);
    
    if(num_giochi==0){
        printf("\nNessun gioco presente nel catalogo\n");
        return;
    }else if(num_giochi>MAX_GIOCHI){
        printf("\nTroppi giochi nel catalogo (massimo %d)\n", MAX_GIOCHI);
        return;
    }
    
    //Legge tutti i giochi dal file
    file=fopen(nomeFile, "rb");
    if(file==NULL){
        printf("\nErrore nell'apertura del file per la lettura\n");
        return;
    }
    
    for(int i=0; i<num_giochi; i++){
        fread(&catalogo[i], sizeof(videogame_t), 1, file);
        
        // Utilizza la funzione StatisticaRecensione per calcolare la media
        medie_recensioni[i] = StatisticaRecensione(nomeFile, catalogo[i].nome, catalogo[i]);
    }
    fclose(file);
    
    // Shell Sort per media recensioni (ordine decrescente)
    int intervallo=num_giochi/2;
    while(intervallo>0){
        for(int i=intervallo; i<num_giochi; i++){
            videogame_t temp_gioco=catalogo[i];
            float temp_media=medie_recensioni[i];
            int j=i;
            // I giochi senza recensioni (media <= 0) vanno in fondo
            while(j>=intervallo && 
                  ((medie_recensioni[j-intervallo]<=0.0 && temp_media>0.0) ||
                   (medie_recensioni[j-intervallo]>0.0 && temp_media>0.0 && 
                    medie_recensioni[j-intervallo]<temp_media))){
                catalogo[j]=catalogo[j-intervallo];
                medie_recensioni[j]=medie_recensioni[j-intervallo];
                j-=intervallo;
            }
            catalogo[j]=temp_gioco;
            medie_recensioni[j]=temp_media;
        }
        intervallo/=2;
    }
    
    //Output finale ordinato con statistiche integrate
    printf("\n---CLASSIFICA GIOCHI PER MEDIA RECENSIONI---\n");
    for(int i=0; i<num_giochi; i++){
        printf("\n%d. %s", i+1, catalogo[i].nome);
        
        if(medie_recensioni[i]>0.0){
            printf("\nMedia recensioni: %.2f/5", medie_recensioni[i]);
        } else {
            printf("\nMedia recensioni: Non disponibile");
        }
        
        printf("\nSviluppatore: %s", catalogo[i].sviluppatore);
        printf("\nAnno: %d", catalogo[i].anno_uscita);
        printf("\nCopie vendute: %d", catalogo[i].copie_vendute);
        
        printf("\n---------------------------");
    }
}