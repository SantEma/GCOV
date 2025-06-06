/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

int Menu(){
    //Impostazione del flag per decretare il ruolo del visitatore al catalogo
    short check_admin=0;
    char input_password[10]; //lunghezza media della password prescelta per gli admin e per i visualizzatori

    //Fase di -> Autentificazione
    printf("\nSi prega di indentificarsi inserendo la password riconosciuta per gli admin, altrimenti digitare 'visitatore' come riportato.\nRicordiamo che si ha solo una possibilita' per inserire la passowrd\nAltrimenti bisognera' riavviare il programma se la si vuole rinserire correttamente senza essere accettati come 'visitatore' -->");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = 0; // Rimuove il newline finale

    //Controllo della password inserita
    if(strcmp(input_password, PASSWORD)==0){
        check_admin=1;
        printf("\nPassword corretta, benvenuto amministratore");
    }
    else if(strcmp(input_password,"visitatore")==0) printf("\nPassword corretta, benvenuto visitatore");
    else printf("\nPassword errata, benvenuto visitatore");

    //Fase di -> Scelta
    short scelta=0;
    if(check_admin==1){
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n1-Ricerca prodotto\n3-Visualizzare una recensione\n");
        scanf("%hd", &scelta);
        while (getchar() != '\n'); // Svuota il buffer, per evitare problemi con l'input successivo nella ricerca
    }
    else{
        printf("\nDigitare il corrispettivo numero per eseguire la scelta desiderata:\n2-Ricerca prodotto per visualizzare o aggiungere una recensione\n");
    }

        //Fase di -> Statistiche
        /* La statistica  può essere fatta da entrambi per calcolare la media di ogni recensione
         * posta da ogni utente
        */

        //Fase di -> Ordinamento
        /* L'ordinamento può essere fatto  da entrambi per ordinare i videogiochi nel catalogo per filtrare il catalogo in base a due opazioni
         * O per media recensione
         * O per copie vendute
         */
    return scelta;
}
    