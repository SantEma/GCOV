/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void MenuPrincipale(videogame_t videogioco){
    //Impostazione del flag per decretare il ruolo del visitatore al catalogo
    short sceltaprincipale=0;
    int check_admin=0;
    
    //Fase di autentificazione
    do{
        printf("\nBenvenuti!\nScegliere come ci si vuole autenticare:\n1)Admin\n2)Visitatore\n-1)Uscire\nScelta:");
        scanf("%hd", &sceltaprincipale);
        while (getchar()!='\n'); // Svuota il buffer
        
        switch(sceltaprincipale){
            case 1:
                check_admin=AutenticazioneAdmin();
                if(check_admin==1){
                    MenuAdmin(videogioco, "catalogo.dat", 1);
                }
                else if(check_admin==0){
                    MenuVisitatore(videogioco, "catalogo.dat", 0);
                }
                break;
            case 2:
                printf("\nBenvenuto visitatore!\n");
                MenuVisitatore(videogioco, "catalogo.dat", 0);
                break;
            case -1:
                printf("\nUscita dal programma...\n");
                break;
            default:
                printf("\nScelta errata, reinserire\n");
                sceltaprincipale=0;
                break;
        }
    }while(sceltaprincipale!=-1);
}

void MenuAdmin(videogame_t videogioco, char *nomeFile, short check_admin){
    short sceltadmin=0; //Variabile per la scelta dell'operazione da eseguire
    do{
        printf("\n\n--- MENU AMMINISTRATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata\n1) Ricerca prodotto\n-1) Uscire dal Menu\nScelta:");
        scanf("%hd", &sceltadmin);
        while (getchar()!='\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        
        switch (sceltadmin){
            case 1:
                Ricerca(nomeFile, videogioco,check_admin);
                break;
            //Pronto per ordinamento
            case -1:
                printf("\nUscita dal menu...\n");
                break;
            default:
                printf("\nScelta non valida, riprova: ");
                sceltadmin=0;
                break;
        }
    }while(sceltadmin!=-1);
}

void MenuVisitatore(videogame_t videogioco, char* nomeFile, short check_admin){
    short sceltaguest=0;
    
    do{
        printf("\n\n--- MENU VISITATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1) Ricerca prodotto\n-1) Uscire dal Menu\nScelta:");
        scanf("%hd", &sceltaguest);
        
        while (getchar()!='\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        switch(sceltaguest){
            case 1:
                //Visualizza l'intero catalogo dei videogiochi
                printf("\nEcco il catalogo dei videogiochi disponibili e alcuni dettagli cosi' da guidarti nella tua scelta:\n");
                VisualizzaCat(nomeFile, videogioco);
                //Fase di ricerca del gioco
                Ricerca(nomeFile, videogioco,check_admin);
                break;
            //Pronto per ordinamento
            case -1:
                printf("\nUscita dal programma...\n");
                break;
            
            default:
                printf("\nScelta non valida, riprova:");
                sceltaguest=0;
                break;
        }

    }while(sceltaguest!=-1);
}

int AutenticazioneAdmin(){
    char input_password[MAX_CARATTERI_PASSWORD];
    short scelta_errore=0;
    
    do{
        printf("\nInserire la password di amministratore: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")] = 0; // Rimuove il newline finale
        
        //Controllo della password inserita
        if(strcmp(input_password, PASSWORD) == 0){
            printf("\nPassword corretta, benvenuto amministratore!\n");
            return 1;
        }
        else{
            printf("\nPassword errata!\nCosa si vuole fare?\n1)Riprovare con un'altra password\n2)Continuare come visitatore\n3)Uscire dal programma\n");
            printf("Scelta: ");
            
            do{
                scanf("%hd", &scelta_errore);
                while (getchar()!='\n'); // Svuota il buffer
                
                switch(scelta_errore){
                    case 1:
                        // Continua il ciclo per riprovare
                        break;
                    case 2:
                        printf("\nBenvenuto visitatore!\n");
                        return 0; 
                    case 3:
                        printf("\nUscita dal programma...\n");
                        return -1; 
                    default:
                        printf("\nScelta non valida, riprova (1-3): ");
                        scelta_errore=0;
                        break;
                }
            }while(scelta_errore<1 || scelta_errore>3);
            
            // Se l'utente ha scelto di riprovare (caso 1), continua il ciclo principale
            if(scelta_errore!=1){
                break; // Esce dal ciclo se ha scelto opzione 2 o 3
            }
        }
    }while(scelta_errore==1);
    
    return -1; // Dovrebbe essere irraggiungibile, ma per sicurezza
}