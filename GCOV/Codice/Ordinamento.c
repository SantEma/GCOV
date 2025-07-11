#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void Ordinamento_copie_vendute(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile, "rb");

    if (file!=NULL){
        videogame_t catalogo[MAX_GIOCHI]; //Catalogo temporaneo, viene utilizzato per riordinare 
        int num_giochi=0;

        while (num_giochi < MAX_GIOCHI && fread(&catalogo[num_giochi], sizeof(videogame_t), 1, file)==1){ // Si leggono tutti i record dal file binario e li si carica nell'array 'temporaneo
            num_giochi++;
        }
        fclose(file);

        if (num_giochi==0){
            printf("\nNessun gioco presente nel catalogo\n");
            return;
        }

        //Shell sort (ordine decrescente)
        int intervallo=num_giochi/2; //Intervallo iniziale, verrà ridotto progressivamente
        while (intervallo>0){
            for (int i=intervallo; i<num_giochi; i++){
                videogame_t temp=catalogo[i];//Variabile temporanea per salvarsi la posizione corrente
                int j=i;
                while (j>=intervallo && catalogo[j-intervallo].copie_vendute<temp.copie_vendute){
                    catalogo[j]=catalogo[j-intervallo];
                    j-=intervallo;
                }
                catalogo[j]=temp; 
            }
            intervallo=intervallo/2; //Riduzione dell'intervallo 
        }

        //Stampa dell'elenco dei giochi ordinato per copie vendute
        printf("\n---CLASSIFICA GIOCHI PER COPIE VENDUTE---\n");
        for(int i=0; i<num_giochi; i++){
            //La media di copie 
            float media_copie=StatisticaCopieVendute(nomeFile, catalogo[i].nome, catalogo[i]);

            printf("\n-------------------------------------\n");
            printf("%s\n", catalogo[i].nome);
            printf("Copie vendute: %d\n", catalogo[i].copie_vendute);
            if (catalogo[i].copie_vendute>=0) {
                 printf("Statistica vendite (in rapporto su max produzione): %.2f\n", media_copie);
            }
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
            // Stampa dei generi del gioco con un separatore 
            if(generi_stampati==0) printf("N/D");
            printf("\n");
            // Stampa delle recensioni numeriche e testuali.
            printf("Recensioni:\n");
            short recensioni_stampate=0;
            for (short x=0; x<MAX_RECENSIONI; x++){
                if (catalogo[i].recensione[x].recensione_num!=-1){
                    printf("- Voto: %d/5", catalogo[i].recensione[x].recensione_num);
                     if (catalogo[i].recensione[x].recensione_scritta[0]!='\0') {
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
    }
    else{
        printf("\nErrore nell'apertura del file per l'ordinamento\n");
    }
}

void Ordinamento_media_recensioni(char *nomeFile, videogame_t videogioco){
    FILE *file = fopen(nomeFile, "rb");
    if(file != NULL){
        videogame_t catalogo[MAX_GIOCHI];
        float medie_recensioni[MAX_GIOCHI];// Array per memorizzare le medie
        int num_giochi=0;
        
        //Calcolo della media delle recensioni
        while(num_giochi<MAX_GIOCHI && fread(&catalogo[num_giochi], sizeof(videogame_t), 1, file)==1){
            medie_recensioni[num_giochi]=StatisticaRecensione(nomeFile, catalogo[num_giochi].nome, catalogo[num_giochi]);
            num_giochi++;
        }
        fclose(file);

        if(num_giochi==0){
            printf("\nNessun gioco presente nel catalogo\n");
            return;
        }

        //Shell sort (ordine decrescente)
        int intervallo=num_giochi/2;
        while(intervallo>0){
            for(int i=intervallo; i<num_giochi; i++){
                //Variabili temporanee per salvarsi la posizione corrente
                videogame_t temp_gioco=catalogo[i];
                float temp_media=medie_recensioni[i];
                int j=i;
                //Spostando un elemento nell'array delle media spostiamo anche l'elemento corrispondente nell'array dei giochi
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
        //Stampa dell'elenco dei giochi ordinato per media recensioni
        printf("\n---CLASSIFICA GIOCHI PER MEDIA RECENSIONI---\n");
        for(int i=0; i<num_giochi; i++){
            printf("\n-------------------------------------\n");
            printf("%s\n", catalogo[i].nome);

            if(medie_recensioni[i]>0.0){
                printf("Media recensioni: %.2f\n", medie_recensioni[i]);
            } else {
                printf("Media recensioni: Non disponibile\n");
            }
            printf("Editore: %s\n", catalogo[i].editore);
            printf("Sviluppatore: %s\n", catalogo[i].sviluppatore);
            if((catalogo[i].descrizione_breve_gioco[0])!='\0'){
                printf("Descrizione: %s\n", catalogo[i].descrizione_breve_gioco);
            }
            printf("Anno: %d\n", catalogo[i].anno_uscita);
            printf("Copie vendute: %d\n", catalogo[i].copie_vendute);

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
            // Stampa delle singole recensioni
            printf("Recensioni:\n");
            short recensioni_stampate=0;
            for (short x=0; x<MAX_RECENSIONI; x++){
                if (catalogo[i].recensione[x].recensione_num!=-1){
                    printf("- Voto: %d/5", catalogo[i].recensione[x].recensione_num);
                     if (catalogo[i].recensione[x].recensione_scritta[0]!='\0') {
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
    } else {
        printf("\nErrore nell'apertura del file per l'ordinamento\n");
    }
}