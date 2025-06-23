#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Inserire il commentary doxygen

int main(){
    ScriviCatalogo("catalogo.dat"); // Creazione del file catalogo.dat con i videogiochi iniziali
    MenuPrincipale(); //Attivazione del menu principale per la gestione del catalogo
    return 0;
}