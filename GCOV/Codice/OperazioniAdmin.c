/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la modifica di un gioco
void ModificaGioco(char *nomeFile, videogame_t videogioco, char *nome_ricerca){
    FILE *file= fopen(nomeFile, "rb+");
    short campo_modifica=0; //variabile per la scelta del campo da modificare
    short x=0; //variabile per il ciclo di modifica del gioco
    int pos=-1; //variabile per la posizione del gioco da modificare
    long offset=0; //variabile per salvare la posizione trovata

    if(file != NULL){
        //verfifca della posizione del gioco da modificare
        int found_pos=0;
        while(fread(&videogioco,sizeof(videogame_t),1,file)==1){
            if(strcmp(videogioco.nome,nome_ricerca)==0) pos = found_pos;
            found_pos++;
        }
        
        //Modifica campi del gioco
        printf("\nChe campo vuoi modificare del gioco '%s'?\n", nome_ricerca);
        do{
            printf("1 - Nome\n2 - Editore\n3 - Sviluppatore\n4 - Descrizione breve del gioco\n5 - Anno di uscita\n6 - Genere\n");
            do{
                scanf("%hd", &campo_modifica);
                if(campo_modifica < 1 || campo_modifica > 6){
                    printf("\nScelta non valida, riprova: ");
                }
            }while(campo_modifica < 1 || campo_modifica > 6); // Assicura che il campo sia tra 1 e 6
            
            switch (campo_modifica) {
            case 1:
                /* nome */
                printf("\nInserisci il nuovo nome del gioco: ");
                while (getchar() != '\n');
                fgets(videogioco.nome, sizeof(videogioco.nome), stdin);
                videogioco.nome[strcspn(videogioco.nome, "\n")] = 0; // Rimuove il newline finale
                break;
            
            case 2:
                /* editore */
                printf("\nInserisci il nuovo nome dell'editore: ");
                while(getchar()!='\n');
                fgets(videogioco.editore,sizeof(videogioco.editore),stdin);
                videogioco.editore[strcspn(videogioco.editore, "\n")]=0;
                break;

            case 3:
                /* sviluppatore */
                printf("\nInserisci il nuovo nome dello sviluppatore: ");
                while(getchar()!='\n');
                fgets(videogioco.sviluppatore,sizeof(videogioco.sviluppatore),stdin);
                videogioco.sviluppatore[strcspn(videogioco.sviluppatore, "\n")]=0;
                break;
            
            case 4:
                /* desc */
                printf("\nInserisci la nuova descrizione breve del videogioco: ");
                while(getchar()!='\n');
                fgets(videogioco.descrizione_breve_gioco,sizeof(videogioco.descrizione_breve_gioco),stdin);
                videogioco.descrizione_breve_gioco[strcspn(videogioco.descrizione_breve_gioco, "\n")]=0;
                break;
            
            case 5:
                /* anno di uscita */
                printf("\nInserire il nuovo anno di uscita del videogioco: ");
                scanf("%d",&videogioco.anno_uscita);
                break;
            
            case 6:
                /* genere */
                printf("\nInserisci il nuovo genere del videogioco: ");
                fgets(videogioco.genere, sizeof(videogioco.genere), stdin);
                videogioco.genere[strcspn(videogioco.genere, "\n")] = '\0';
                break;    
            
            default:
                break;
            }

            fseek(file,pos*sizeof(videogame_t),SEEK_SET);
            if(fwrite(&videogioco,sizeof(videogame_t),1,file)!=1) printf("\nErrore nella scrittura del record");
            else printf("\nModifica effettuata con successo");

            printf("\nSe vuoi continuare a modificare il gioco, digita 1, altrimenti 0 per uscire: ");
            scanf("%hd", &x);
        }while(x==1);

        // Stampa le modifiche apportate
        fseek(file,0,SEEK_SET);

        printf("\nQueste sono state le modifiche apportate");
        while(fread(&videogioco,sizeof(videogame_t),1,file)==1){
            printf("\nNome: %s", videogioco.nome);
            printf("\nEditore: %s", videogioco.editore);
            printf("\nSviluppatore: %s", videogioco.sviluppatore);
            printf("\nDescrizione: %s", videogioco.descrizione_breve_gioco);
            printf("\nAnno di uscita: %d", videogioco.anno_uscita);
            printf("\nGenere: %s", videogioco.genere);
            printf("\nRecensione: %d", videogioco.recensione);
            printf("\nCopie vendute: %d\n", videogioco.copie_vendute);
        }

        fclose(file);
    }
    else printf("\nErrore nell'apertura del file per la modifica del gioco");
}

void AggiungiGioco(char *nomeFile, videogame_t videogioco){
    printf("Da implementare\n");
}

void CancellaGioco(char *nomeFile, videogame_t videogioco, char *nome_ricerca){

    FILE *file_originale=fopen(nomeFile,"rb"); //Apre il file dati in lettura binaria.
    FILE *file_temporaneo=fopen("temp.dat","wb"); //Crea un file temporaneo in scrittura binaria.
    int trovato=0; //Flag per verificare se il gioco è stato trovato.

    //Controlla se i file sono stati aperti correttamente.
    if(file_originale==NULL||file_temporaneo==NULL){
        printf("\nErrore nell'apertura dei file per la cancellazione.");
        return; //Termina la funzione in caso di errore.
    }

    //Scorre ogni record (videogioco) nel file originale.
    while(fread(&videogioco,sizeof(videogame_t),1,file_originale)==1){
        //Se il nome del gioco corrente è diverso da quello da cancellare lo scrive nel file temporaneo.
        if(strcmp(videogioco.nome,nome_ricerca)!=0){
            fwrite(&videogioco,sizeof(videogame_t),1,file_temporaneo);
        }
        else trovato=1; //Se il nome del gioco corrente corrisponde a quello da cancellare, imposta il flag trovato a 1.
    }

    fclose(file_originale);
    fclose(file_temporaneo);

    if(trovato){
        remove(nomeFile); 
        rename("temp.dat",nomeFile); //Rinomina il file temporaneo con il nome dell'originale, altrimenti, se non trovato, elimina il file temporaneo.
        printf("\nGioco '%s' cancellato con successo.\n",nome_ricerca);
    }else{
        remove("temp.dat");
        printf("\nGioco '%s' non trovato nel catalogo.\n",nome_ricerca);
    }
}
