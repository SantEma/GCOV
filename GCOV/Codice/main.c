#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Inserire il commentary doxygen

int main(){
    videogame_t videogame;
    ScriviCatalogo("catalogo.dat"); // Creazione del file catalogo.dat con i videogiochi iniziali
    int scelta=Menu();

    //Da inserire il ciclo ancora per la scelta del menu

    switch (scelta){
        case 1:
            RicercaAdmin("catalogo.dat",videogame);
            break;
    
        case 2:
            RicercaVisitatore("catalogo.dat",videogame);
            break;
        /*case 3
    
        */

        default:
            break;
    }

    return 0;
}