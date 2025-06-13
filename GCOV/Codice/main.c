#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Inserire il commentary doxygen

int main(){
    videogame_t videogame;
    ScriviCatalogo("catalogo.dat"); // Creazione del file catalogo.dat con i videogiochi iniziali
    MenuPrincipale(videogame); //Attivazione del menu principale per la gestione del catalogo
    return 0;
}