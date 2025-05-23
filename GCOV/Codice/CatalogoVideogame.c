/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la creazione del catalogo
void ScriviCatalogo(char *nomeFile, Videogame_T catalogo){
    short flag=1; //Controllare se il file è stato creato correttamente
    int num_videogame=0;
    FILE* file=fopen(nomeFile, "wb");
    if(file!=NULL){
        printf("\nInserire quanti videogiochi sono presenti nel catalogo: ");
        scanf("%d", &num_videogame);
        if(num_videogame<=0); //continuare
    }
}