#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la modifica di un gioco
void ModificaGioco(char *nomeFile, char *nome_ricerca, videogame_t videogioco,short pos){
    FILE *file=fopen(nomeFile, "rb+"); 
    short campo_modifica=0; //Variabile per la scelta del campo da modificare
    short x=0; //Variabile per il ciclo di modifica del gioco

    if(file!=NULL){
        //Modifica campi del gioco
        printf("\nChe campo vuoi modificare del gioco '%s'?\n", nome_ricerca);
        do{
            printf("1)Nome\n2)Editore\n3)Sviluppatore\n4)Descrizione breve del gioco\n5)Anno di uscita\n6)Genere\n");
            do{
                scanf("%hd", &campo_modifica);
                if(campo_modifica<1 || campo_modifica>6){
                    printf("\nScelta non valida, riprova: ");
                }
            }while(campo_modifica<1 || campo_modifica>6); 
            
            switch(campo_modifica) {
            case 1:
               //Nome del gioco
                printf("\nInserisci il nuovo nome del gioco: ");
                while (getchar()!='\n'); // Svuota il buffer, per evitare problemi con l'input successivo
                fgets(videogioco.nome, sizeof(videogioco.nome), stdin);
                videogioco.nome[strcspn(videogioco.nome, "\n")] = 0; // Rimuove il newline finale
                break;
            
            case 2:
                //Editore del gioco
                printf("\nInserisci il nuovo nome dell'editore: ");
                while(getchar()!='\n');// Svuota il buffer, per evitare problemi con l'input successivo
                fgets(videogioco.editore,sizeof(videogioco.editore),stdin);
                videogioco.editore[strcspn(videogioco.editore, "\n")]=0;
                break;

            case 3:
                //Sviluppatore del gioco
                printf("\nInserisci il nuovo nome dello sviluppatore: ");
                while(getchar()!='\n');
                fgets(videogioco.sviluppatore,sizeof(videogioco.sviluppatore),stdin);
                videogioco.sviluppatore[strcspn(videogioco.sviluppatore, "\n")]=0;
                break;
            
            case 4:
                //Descrizione del gioco
                printf("\nInserisci la nuova descrizione breve del videogioco: ");
                while(getchar()!='\n');
                fgets(videogioco.descrizione_breve_gioco,sizeof(videogioco.descrizione_breve_gioco),stdin);
                videogioco.descrizione_breve_gioco[strcspn(videogioco.descrizione_breve_gioco, "\n")]=0;
                break;
            
            case 5:
                //Anno di uscita del gioco
                printf("\nInserire il nuovo anno di uscita del videogioco: ");
                scanf("%d",&videogioco.anno_uscita);
                break;
            
            case 6:
                //Genere del gioco 
                printf("\nInserisci il nuovo genere del videogioco: ");
                while(getchar()!='\n');
                fgets(videogioco.genere[0], sizeof(videogioco.genere[0]), stdin);
                videogioco.genere[0][strcspn(videogioco.genere[0], "\n")]='\0';
                break;    
            
            default:
                printf("\nScelta sbagliata,reinserire\n");
                campo_modifica=0;
                break;
            }

            fseek(file,pos*sizeof(videogame_t),SEEK_SET);
            if(fwrite(&videogioco,sizeof(videogame_t),1,file)!=1) printf("\nErrore nella scrittura del record");
            else printf("\nModifica effettuata con successo");

            printf("\nSe vuoi continuare a modificare il gioco, digita 1, altrimenti 0 per uscire: ");
            scanf("%hd", &x);
        }while(x==1);

        // Stampa le modifiche apportate e riportare il puntatore all'inizio del file in caso di ulteriori operazioni
        fseek(file,0,SEEK_SET);
        printf("\nModifiche apportate con successo\n");

        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per la modifica del gioco\n");
}


void CancellaGioco(char *nomeFile, char *nome_ricerca, videogame_t videogioco, short pos){

    FILE *file_originale=fopen(nomeFile,"rb");
    FILE *file_temporaneo=fopen("temp.dat","wb"); //Crea un file temporaneo in scrittura binaria.
    int trovato=0; //Flag per verificare se il gioco è stato trovato.

    //Controlla se i file sono stati aperti correttamente.
    if(file_originale==NULL||file_temporaneo==NULL){
        printf("\nErrore nell'apertura dei file per la cancellazione.\n");
        return; //Termina la funzione in caso di errore.
    }

    //Scorre ogni videogioco nel file originale.
    while(fread(&videogioco,sizeof(videogame_t),1,file_originale)==1){
        //Se il nome del gioco corrente è diverso da quello da cancellare lo scrive nel file temporaneo
        if(strcmp(videogioco.nome,nome_ricerca)!=0){
            fwrite(&videogioco,sizeof(videogame_t),1,file_temporaneo);
        }
        else trovato=1;
    }

    fclose(file_originale);
    fclose(file_temporaneo);

    //Se il gioco viene trovato il file originale viene cancellato e quello temporaneo rinominato con il nome dell'originale, altrimenti viene soltanto eliminato quello temporaneo
    if(trovato){
        remove(nomeFile); 
        rename("temp.dat",nomeFile); 
        printf("\nGioco '%s' cancellato con successo.\n",nome_ricerca);
    }else{
        remove("temp.dat");
        printf("\nGioco '%s' non trovato nel catalogo.\n",nome_ricerca);
    }
}


void AggiungiGioco(char *nomeFile, videogame_t videogioco){
    FILE *file=fopen(nomeFile,"rb+");
    short x=0; //variabile per il ciclo di modifica del gioco
    short scelta_descrizione=0; //Variabile per la scelta dell'inseirmento della descrizione
    
    if(file!=NULL){
        //Inserimento nuovo gioco
        do{
            //Nome
            printf("\nInserire il nome: ");
            while(getchar()!='\n');
            fgets(videogioco.nome,sizeof(videogioco.nome),stdin);
            videogioco.nome[strcspn(videogioco.nome, "\n")]=0;

            //Editore
            printf("\nInserire l'editore: ");
            fgets(videogioco.editore,sizeof(videogioco.editore),stdin);
            videogioco.editore[strcspn(videogioco.editore, "\n")]=0;

            //Sviluppatore
            printf("\nInserire lo sviluppatore: ");
            fgets(videogioco.sviluppatore,sizeof(videogioco.sviluppatore),stdin);
            videogioco.sviluppatore[strcspn(videogioco.sviluppatore, "\n")]=0;

            //Descrizione (opzionale-+)
            printf("\nVuoi inserire la descrizione?: 1-Si 0-No: ");
            scanf("%hd", &scelta_descrizione);
            if(scelta_descrizione==1){
                printf("\nInserire la descrizione del gioco: ");
                getchar();
                fgets(videogioco.descrizione_breve_gioco,sizeof(videogioco.descrizione_breve_gioco),stdin);
                videogioco.descrizione_breve_gioco[strcspn(videogioco.descrizione_breve_gioco, "\n")]=0;
            }

            //Anno uscita
            printf("\nInserire l'anno di uscita: ");
            scanf("%d",&videogioco.anno_uscita); 
            
            //Genere
            int num_generi=0;
            printf("\nQuanti generi vuoi inserire? Rispetta sempre il massimo valore di %d: ", MAX_RECENSIONI);
            scanf("%d",&num_generi);
            getchar();
            if(num_generi>MAX_RECENSIONI) num_generi = MAX_RECENSIONI; //eliminare i valori in più per potrarlo al valore della costante
            for(short i=0;i<num_generi;i++){
                printf("Inserisci il genere %hd: ",i+1);
                fgets(videogioco.genere[i], sizeof(videogioco.genere[i]), stdin);
                videogioco.genere[i][strcspn(videogioco.genere[i], "\n")] ='\0';
            }

            //Altri dati per gli utenti
            videogioco.copie_vendute=0;
            for(short i=0;i<MAX_RECENSIONI;i++){
                videogioco.recensione[i].recensione_num=-1; //Inizializza la recensione a -1, dato che 0 è un valore valido
                videogioco.recensione[i].recensione_scritta[0]='\0';
            }

            //Aggiornamento dati del file con fseek
            fseek(file,0,SEEK_END);
            if(fwrite(&videogioco,sizeof(videogame_t),1,file)!=1) printf("\nErrore nella scrittura del record sul file");
            else printf("\nGioco aggiunto");

            //Riposizionamento del pointer all'inizio del file
            fseek(file,0,SEEK_SET);

            printf("\nSe vuoi continuare ad aggiungere un gioco, digita 1, altrimenti 0 per uscire: ");
            scanf("%hd", &x);
        }while(x==1);

        printf("\nTutti i giochi sono stati aggiunti correttamente\n");

        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per l'aggiunta del gioco\n");
}