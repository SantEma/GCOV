#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void MenuPrincipale(){
    videogame_t videogioco; // Struttura per il gioco da ricercare

    short sceltaprincipale=0; //Scelta dell'utente nel menu principale
    int check_admin=0; // Booleana presente per poter identificare l'utente per tutte le sue operazioni, di default è falsa in modo da autenticarsi da visitatore
    
    //Fase di autentificazione, l'utente viene sempre considerato visitatore fin tanto che non si autentica
    do{
        printf("\nBenvenuti!\nScegliere come ci si vuole autenticare:\n1)Admin\n2)Visitatore\n-1)Uscire\nScelta:");
        scanf("%hd", &sceltaprincipale);
        while (getchar()!='\n'); // Svuota il buffer
        
        switch(sceltaprincipale){
            case 1:
                check_admin=AutenticazioneAdmin(); //Assegnazione del valore di ritorno della variabile autenticazione admin
                switch(check_admin){
                    case 0:
                    MenuVisitatore(videogioco, "catalogo.dat", check_admin);
                    case 1:
                    MenuAdmin(videogioco, "catalogo.dat", check_admin);
                }
                break;
            case 2:
                printf("\nBenvenuto visitatore!\n");
                MenuVisitatore(videogioco, "catalogo.dat", check_admin);
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
    short sceltadmin=0; //Variabile per la scelta dell'operazione da eseguire per l'admin
    do{
        printf("\n\n--- MENU AMMINISTRATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata\n1) Ricerca prodotto\n2) Ordinamento giochi\n-1) Uscire dal Menu\nScelta:");
        scanf("%hd", &sceltadmin);
        while (getchar()!='\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        
        switch (sceltadmin){
            case 1:
                Ricerca(nomeFile, videogioco,check_admin);
                break;
            case 2:
                {
                    short scelta_ordinamento=0;
                    printf("\nScegli il tipo di ordinamento:\n1)Ordinamento per copie vendute\n2)Ordinamento per statistiche recensioni\nScelta: ");
                    do{
                        scanf("%hd", &scelta_ordinamento);
                        while (getchar()!='\n'); // Svuota il buffer
                        
                        switch(scelta_ordinamento){
                            case 1:
                                Ordinamento_copie_vendute(nomeFile, videogioco);
                                break;
                            case 2:
                                Ordinamento_media_recensioni(nomeFile, videogioco);
                                break;
                            default:
                                printf("\nScelta non valida, riprova (1-2): ");
                                scelta_ordinamento=0;
                                break;
                        }
                    }while(scelta_ordinamento<1 || scelta_ordinamento>2);
                }
                break;
            case -1:
                printf("\nUscita dal menu...\n");
                break;
            default:
                printf("\nScelta non valida, riprova(1,2,-1): ");
                sceltadmin=0;
                break;
        }
    }while(sceltadmin!=-1);
}

void MenuVisitatore(videogame_t videogioco, char* nomeFile, short check_admin){
    short sceltaguest=0;
    
    do{
        printf("\n\n--- MENU VISITATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1) Ricerca prodotto\n2) Ordinamento giochi\n-1) Uscire dal Menu\nScelta:");
        scanf("%hd", &sceltaguest);
        
        while (getchar()!='\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        switch(sceltaguest){
            case 1:
                //Fase di ricerca del gioco
                Ricerca(nomeFile, videogioco,check_admin);
                break;
            case 2:
                {
                    short scelta_ordinamento=0;
                    printf("\nScegli il tipo di ordinamento:\n1) Ordinamento per copie vendute\n2) Ordinamento per statistiche recensioni\nScelta: ");
                    do{
                        scanf("%hd", &scelta_ordinamento);
                        while (getchar()!='\n'); // Svuota il buffer
                        
                        switch(scelta_ordinamento){
                            case 1:
                                Ordinamento_copie_vendute(nomeFile, videogioco); 
                                break;
                            case 2:
                                Ordinamento_media_recensioni(nomeFile, videogioco);
                                break;
                            default:
                                printf("\nScelta non valida, riprova (1-2): ");
                                scelta_ordinamento=0;
                                break;
                        }
                    }while(scelta_ordinamento<1 || scelta_ordinamento>2);
                }
                break;
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
    short scelta_errore=0; //Variabile per immagazzinare la scelta ove entri in questa funzione
    
    do{
        printf("\nInserire la password di amministratore: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")]=0; // Rimuove il newline finale
        
        //Controllo della password inserita
        if(strcmp(input_password, PASSWORD)==0){
            printf("\nPassword corretta, benvenuto amministratore!\n");
            return 1;
        }
        else{
            printf("\nATTENZIONE!Password errata!\nCosa si vuole fare?\n1)Riprovare l'inserimento\n2)Continuare come visitatore\n3)Uscire dal programma\nScelta: ");
            //L'utente viene sollecitato a riemettere la password se autorizzato (così da non far riavviare il programma nel caso la voglia reimettere), altrimenti diventa un semplice utente
            do{
                scanf("%hd", &scelta_errore);
                while (getchar()!='\n');//Svuota il buffer
                
                switch(scelta_errore){
                    case 1:
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
            if(scelta_errore!=1){
                break;
            }
        }
    }while(scelta_errore==1);
    
}