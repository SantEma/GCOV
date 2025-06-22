/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"



void Ordinamento_copie_vendute(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");
    if(file==NULL){
        printf("\nErrore nell'apertura del file per l'ordinamento per copie vendute\n");
        return;
    }
    //Array per i giochi da riordinare
    videogame_t catalogo[MAX_GIOCHI];
    
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
    }
    fclose(file);
    
    //Shell sort per copie vendute, si presuppone sia in ordine decrescente
    int intervallo=num_giochi/2;
    while(intervallo>0){
        for(int i=intervallo; i<num_giochi; i++){
            videogame_t temp=catalogo[i];
            int j=i;
            while(j>=intervallo && catalogo[j-intervallo].copie_vendute<temp.copie_vendute){
                catalogo[j]=catalogo[j-intervallo];
                j-=intervallo;
            }
            catalogo[j]=temp;
        }
        intervallo /= 2;
    }
    
    //Output finale ordinato
    printf("\n---CLASSIFICA GIOCHI PER COPIE VENDUTE---\n");
    for(int i=0; i<num_giochi; i++){
        printf("\n%d. %s", i+1, catalogo[i].nome);
        printf("\nCopie vendute: %d", catalogo[i].copie_vendute);
        printf("\nSviluppatore: %s", catalogo[i].sviluppatore);
        printf("\nAnno: %d", catalogo[i].anno_uscita);
        printf("\n---------------------------");
    }
}

void Ordinamento_statistiche(char *nomeFile, videogame_t videogioco){
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
    
        //Calcola la media delle recensioni per ogni gioco
        float somma=0.0;
        int contatore=0;
        for(int j=0; j<MAX_RECENSIONI; j++){
            if(catalogo[i].recensione[j].recensione_num!=-1){
                somma+=catalogo[i].recensione[j].recensione_num;
                contatore++;
            }
        }
        if (contatore > 0) medie_recensioni[i] = somma / contatore;
        else medie_recensioni[i] = -1.0; // -1 quando le recensioni non ci sono

    }
    fclose(file);
    
    // Shell Sort per media recensioni (ordine decrescente)
    int intervallo=num_giochi/2;
    while(intervallo>0){
        for(int i=intervallo; i<num_giochi; i++){
            videogame_t temp_gioco=catalogo[i];
            float temp_media=medie_recensioni[i];
            int j=i;
            // I giochi senza recensioni vanno in fondo
            while(j>=intervallo && 
                  ((medie_recensioni[j-intervallo]==-1.0 && temp_media!=-1.0) ||
                   (medie_recensioni[j-intervallo]!=-1.0 && temp_media!=-1.0 && 
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
    
    //Output finale ordinato
    printf("\n---CLASSIFICA GIOCHI PER MEDIA RECENSIONI---\n");
    for(int i=0; i<num_giochi; i++){
        printf("\n%d. %s", i+1, catalogo[i].nome);
        if(medie_recensioni[i]!=-1.0){
            printf("\nMedia recensioni: %.2f/5", medie_recensioni[i]);
        }
        else{
            printf("\nMedia recensioni: Non disponibile");
        }
        printf("\nSviluppatore: %s", catalogo[i].sviluppatore);
        printf("\nAnno: %d", catalogo[i].anno_uscita);
        printf("\nCopie vendute: %d", catalogo[i].copie_vendute);
        printf("\n---------------------------");
    }
}