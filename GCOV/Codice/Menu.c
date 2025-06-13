/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

void MenuPrincipale(){
    //Impostazione del flag per decretare il ruolo del visitatore al catalogo
    short check_admin=0;
    char input_password[MAX_CARATTERI]; //Lunghezza media della password prescelta per gli admin e per i visualizzatori

    //Fase di autentificazione
    printf("\nSi prega di indentificarsi inserendo la password riconosciuta per gli admin, altrimenti digitare 'visitatore' come riportato.\nRicordiamo che si ha solo una possibilita' per inserire la passowrd,altrimenti bisognera' riavviare il programma : ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Rimuove il newline finale
    
    //Controllo della password inserita
    if(strcmp(input_password, PASSWORD)==0){
        check_admin=1;
        printf("\nPassword corretta, benvenuto amministratore!");
        MenuAdmin(); // Riportiamo al menu dell'amministratore
    }
    else if(strcmp(input_password,"visitatore")==0){
        printf("\nPassword corretta, benvenuto visitatore");
        MenuVisitatore();
        // Riportiamo al menu del visitatore
    }
    else{
        printf("\nPassword errata, benvenuto visitatore");
        MenuVisitatore();
        
    }
}

void MenuAdmin(){
    short SceltaAdmin=0; //Variabile per la scelta dell'operazione da eseguire
    printf("\n\n--- MENU AMMINISTRATORE ---\n");
    printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1-Ricerca prodotto");
    scanf("%hd", &SceltaAdmin);
    while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
    do{
        switch (SceltaAdmin) {
            
        }
        while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
    }while(SceltaAdmin!=-1);
}


void MenuVisitatore(){
    short SceltaGuest=0;
    printf("\n\n--- MENU VISITATORE ---\n");
    printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1-Ricerca prodotto\n3-Visualizzare una recensione\n");
    scanf("%hd", &SceltaGuest);
    while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca

    
}