/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void MenuPrincipale(videogame_t videogame){
    //Impostazione del flag per decretare il ruolo del visitatore al catalogo
    short check_admin=0;
    char input_password[MAX_CARATTERI]; //Lunghezza media della password prescelta per gli admin e per i visualizzatori

    //Fase di autentificazione
    printf("\n--Si prega di indentificarsi inserendo la password riconosciuta per gli admin, altrimenti digitare 'visitatore' come riportato.--\n--Ricordiamo che si ha solo una possibilita' per inserire la passowrd,altrimenti bisognera' riavviare il programma--\nPassword: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")]=0; // Rimuove il newline finale
    
    //Controllo della password inserita
    if(strcmp(input_password, PASSWORD)==0){
        check_admin=1;
        printf("\nPassword corretta, benvenuto amministratore!");
        MenuAdmin(videogame, "catalogo.dat"); // Riportiamo al menu dell'amministratore
    }
    else if(strcmp(input_password,"visitatore")==0){
        printf("\nPassword corretta, benvenuto visitatore");
        MenuVisitatore(videogame, "catalogo.dat");
        // Riportiamo al menu del visitatore
    }
    else{
        printf("\nPassword errata, benvenuto visitatore");
        MenuVisitatore(videogame, "catalogo.dat");
        // Riportiamo al menu del visitatore
    }
}

void MenuAdmin(videogame_t videogame, char *nomeFile){
    short sceltadmin=0; //Variabile per la scelta dell'operazione da eseguire
    
    do{
        printf("\n\n--- MENU AMMINISTRATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1) Ricerca prodotto\n-1) Uscire\nScelta:");
        scanf("%hd", &sceltadmin);

        while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        switch (sceltadmin){
            case 1:
                RicercaAdmin(nomeFile, videogame);
                break;
            case -1:
                printf("\nUscita dal programma...\n");
                break;
            default:
                printf("\nScelta non valida, riprova: ");
                break;
        }

    }while(sceltadmin!=-1);
}

void MenuVisitatore(videogame_t videogame, char* nomeFile){
    short sceltaguest=0;
    
    do{
        printf("\n\n--- MENU VISITATORE ---\n");
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1) Ricerca prodotto:\n-1) Uscire\nScelta:");
        scanf("%hd", &sceltaguest);
        
        while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
        switch(sceltaguest){
            case 1:
                RicercaVisitatore(nomeFile, videogame);
                break;
            case -1:
                printf("\nUscita dal programma...\n");
                break;
            default:
                printf("\nScelta non valida, riprova:");
                break;
        }

    }while(sceltaguest!=-1);
}