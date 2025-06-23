#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void Ordinamento_copie_vendute(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");

    if (file!=NULL){
        videogame_t catalogo[MAX_GIOCHI];
        int num_giochi=0;

        while (num_giochi<MAX_GIOCHI && fread(&catalogo[num_giochi], sizeof(videogame_t), 1, file)==1){
            num_giochi++;
        }
        fclose(file);

        if (num_giochi==0){
            printf("\nNessun gioco presente nel catalogo\n");
            return;
        }

        // Shell sort per copie vendute 
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

        printf("\n---CLASSIFICA GIOCHI PER COPIE VENDUTE---\n");
        for(int i=0; i<num_giochi; i++){
            printf("\n-------------------------------------\n");
            printf("%s\n", catalogo[i].nome);
            printf("Copie vendute: %d\n", catalogo[i].copie_vendute);
            printf("Editore: %s\n", catalogo[i].editore);
            printf("Sviluppatore: %s\n", catalogo[i].sviluppatore);
            printf("Descrizione: %s\n", catalogo[i].descrizione_breve_gioco);
            printf("Anno uscita: %d\n", catalogo[i].anno_uscita);
            printf("Generi: ");
            short generi_stampati=0;
            for(short j=0; j<MAX_GENERI; j++){
                if(catalogo[i].genere[j][0]!='\0'){
                    if(generi_stampati>0) printf(", ");
                    printf("%s", catalogo[i].genere[j]);
                    generi_stampati++;
                }
            }
            if(generi_stampati==0) printf("N/D");
            printf("\n");
            printf("Recensioni:\n");
            short recensioni_stampate=0;
            for (short x=0; x<MAX_RECENSIONI; x++){
                if (catalogo[i].recensione[x].recensione_num!=-1){
                    printf("- Voto: %d/5", catalogo[i].recensione[x].recensione_num);
                     if (strlen(catalogo[i].recensione[x].recensione_scritta) > 0) {
                        printf("| Testo: %s", catalogo[i].recensione[x].recensione_scritta);
                    }
                    printf("\n");
                    recensioni_stampate++;
                }
            }
            if(recensioni_stampate==0) {
                 printf("Nessuna recensione presente.\n");
            }
        } 
        printf("\n-------------------------------------\n");
    }
    else{
        printf("\nErrore nell'apertura del file per l'ordinamento\n");
    }
}

void Ordinamento_media_recensioni(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");
    if(file!=NULL){
        printf("\nErrore nell'apertura del file per l'ordinamento per statistiche\n");
        return;
    

    videogame_t catalogo[MAX_GIOCHI];
    float medie_recensioni[MAX_GIOCHI];
    int num_giochi=0;
    
    while(num_giochi < MAX_GIOCHI && fread(&catalogo[num_giochi], sizeof(videogame_t), 1, file)==1){
        float somma=0;
        short conteggio=0;
        for(short i=0; i<MAX_RECENSIONI; i++) {
            if(catalogo[num_giochi].recensione[i].recensione_num!=-1) {
                somma+=catalogo[num_giochi].recensione[i].recensione_num;
                conteggio++;
            }
        }
        if(conteggio>0) {
            medie_recensioni[num_giochi]=somma/conteggio;
        } else {
            medie_recensioni[num_giochi]=0.0;
        }
        num_giochi++;
    }
    fclose(file);
    
    if(num_giochi==0){
        printf("\nNessun gioco presente nel catalogo\n");
        return;
    }
    
    // Shell Sort per media recensioni 
    int intervallo=num_giochi/2;
    while(intervallo>0){
        for(int i=intervallo; i<num_giochi; i++){
            videogame_t temp_gioco=catalogo[i];
            float temp_media=medie_recensioni[i];
            int j=i;
            while(j>=intervallo && medie_recensioni[j-intervallo]<temp_media){
                catalogo[j]=catalogo[j-intervallo];
                medie_recensioni[j]=medie_recensioni[j-intervallo];
                j-=intervallo;
            }
            catalogo[j]=temp_gioco;
            medie_recensioni[j]=temp_media;
        }
        intervallo/=2;
    }

    printf("\n---CLASSIFICA GIOCHI PER MEDIA RECENSIONI---\n");
    for(int i=0; i<num_giochi; i++){
        printf("\n-------------------------------------\n");
        printf("%s\n", catalogo[i].nome);

        if(medie_recensioni[i]>0.0){
            printf("Media recensioni: %.2f/5\n", medie_recensioni[i]);
        } else {
            printf("Media recensioni: Non disponibile\n");
        }
        printf("Editore: %s\n", catalogo[i].editore);
        printf("Sviluppatore: %s\n", catalogo[i].sviluppatore);
        if(strlen(catalogo[i].descrizione_breve_gioco) > 0){
            printf("Descrizione: %s\n", catalogo[i].descrizione_breve_gioco);
        }
        printf("Anno: %d\n", catalogo[i].anno_uscita);
        printf("Copie vendute: %d\n", catalogo[i].copie_vendute);
        
        printf("Generi: ");
        short generi_stampati = 0;
        for(short j=0; j<MAX_GENERI; j++){
            if(catalogo[i].genere[j][0]!='\0'){
                if(generi_stampati > 0) printf(", ");
                printf("%s", catalogo[i].genere[j]);
                generi_stampati++;
            }
        }
        if(generi_stampati==0) printf("N/D");
        printf("\n");
        
        printf("Recensioni:\n");
        short recensioni_stampate=0;
        for (short x=0; x<MAX_RECENSIONI; x++){
            if (catalogo[i].recensione[x].recensione_num!=-1){
                printf("- Voto: %d/5", catalogo[i].recensione[x].recensione_num);
                 if (strlen(catalogo[i].recensione[x].recensione_scritta) > 0) {
                    printf(" | Testo: %s", catalogo[i].recensione[x].recensione_scritta);
                }
                printf("\n");
                recensioni_stampate++;
            }
        }
        if(recensioni_stampate==0) {
             printf("Nessuna recensione presente.\n");
        }
    }
    printf("\n-------------------------------------\n");
    }else{
        printf("\nErrore nell'apertura del file per l'ordinamento\n");
    }
}