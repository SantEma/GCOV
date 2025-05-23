#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogoVideogame.h"

//Inserire il commentary doxygen

int main(){
    // Impostazione del flag per decretare il ruolo del visitatore al catalogo
    short check_admin=0;
    
    // navigazione nel menù
    short scelta=0;
    printf("\nInserire l'operazione che si vuole eseguire sul catalogo\n1-Cercare videogame\n2-...");
    /* La ricerca del videogame si divide in due tipi:
     * l'admin potrà ricercare un videogame solo per effettuare 3 operazioni madri:
     * MODIFICA, CANCELLAZIONE, VISUALIZZARE RECENSIONE
     * 
     * L'utente invece può solamente ricercare per visualizzare le informazioni di un gioco
     * e aggiungere una recensione
    */ 


    /* TO-DO
        QUESTE FUNZIONI SONO DA IMPLEMENTARE IN UN FILE HEADER A PARTE, NON DA LASCIARE NEL MAIN
    */
}