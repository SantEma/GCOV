/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la modifica di un gioco
void ModificaGioco(char *nomeFile, videogame_t videogioco, char *nome_ricerca){
    FILE *file= fopen(nomeFile, "r+b");
    short campo_modifica=0; //variabile per la scelta del campo da modificare
    short x=0; //variabile per il ciclo di mdofica del gioco
    int pos=-1; //variabile per la posizione del gioco da modificare
    if(file != NULL){
        //verfifca della posizione del gioco da modificare
        while(pos<0){
            scanf("%d",&pos);
            while (getchar() != '\n');
            if(pos<0) printf("\nPosizione non valida, rinserire: ");
        }
        //modifica campi del gioco
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
                printf("\nInserisci il nuovo nome del gioco: ");
                while (getchar() != '\n');
                fgets(videogioco.nome, sizeof(videogioco.nome), stdin);
                videogioco.nome[strcspn(videogioco.nome, "\n")] = 0; // Rimuove il newline finale
                break;
            
            case 2:
                /* code */
                break;

            case 3:
                /* code */
                break;
            
            case 4:
                /* code */
                break;
            
            case 5:
                /* code */
                break;
            
            case 6:
                /* code */
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