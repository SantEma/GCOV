/**
 * Inserire il doxygen
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la creazione del catalogo
void ScriviCatalogo(char *nomeFile){
    //array dei 20 giochi iniziali
    videogame_t catalogo[GIOCHI_START]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, "Avventura", 5},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, "GDR", 5},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, "Azione", 5},
        {"God of War", "Sony", "Santa Monica Studio", "Mitologia nordica reinventata", 2018, "Azione", 5},
        {"Super Mario Odyssey", "Nintendo", "Nintendo EPD", "", 2017, "Platform", 5},
        {"Hollow Knight", "Team Cherry", "Team Cherry", "Metroidvania atmosferico", 2017, "Platform", 4},
        {"Celeste", "Matt Makes Games", "Matt Makes Games", "", 2018, "Platform", 5},
        {"Dark Souls III", "Bandai Namco", "FromSoftware", "Sfida hardcore fantasy", 2016, "GDR", 5},
        {"Elden Ring", "Bandai Namco", "FromSoftware", "Open-world soulslike", 2022, "GDR", 5},
        {"Minecraft", "Mojang", "Mojang Studios", "Costruisci e sopravvivi in mondi infiniti", 2011, "Sandbox", 5},
        {"Stardew Valley", "ConcernedApe", "ConcernedApe", "Fattoria e vita rurale", 2016, "Simulazione", 4},
        {"Hades", "Supergiant Games", "Supergiant Games", "", 2020, "Roguelike", 5},
        {"DOOM Eternal", "Bethesda", "id Software", "Spara e distruggi demoni", 2020, "Sparatutto", 4},
        {"Overwatch", "Blizzard", "Blizzard", "FPS a squadre", 2016, "Sparatutto", 4},
        {"Cyberpunk 2077", "CD Projekt", "CD Projekt RED", "Futuro distopico open-world", 2020, "GDR", 3},
        {"Animal Crossing: New Horizons", "Nintendo", "Nintendo EPD", "", 2020, "Simulazione", 5},
        {"Among Us", "Innersloth", "Innersloth", "Deduzione sociale spaziale", 2018, "Party", 4},
        {"Fortnite", "Epic Games", "Epic Games", "Battle royale cartoonesco", 2017, "Battle Royale", 3},
        {"League of Legends", "Riot Games", "Riot Games", "", 2009, "MOBA", 4},
        {"Tetris", "Nintendo", "Alexey Pajitnov", "", 1984, "Puzzle", 5}
    };

    //verifica se il file esiste già
    FILE* file=fopen(nomeFile, "rb"); // se il file è apribile in rb allora già esiste, bisogna non entrarci
    if(file ==NULL){
        //file non esistente, possiamo inserire i giochi

        short flag=1; //Controllare se il file è stato creato correttamente
        file=fopen(nomeFile, "wb");
        if(file!=NULL){
            if(fwrite(&catalogo, sizeof(videogame_t), GIOCHI_START,file)!=1) flag=0;
            if(!flag) printf("\nErrore nella scrittura");
            else printf("\nSCRITTO");
            fclose(file);
        }
        else printf("\nError");
        }
    else{
        // il file esiste già, non dobbiamo riscriverlo
        fclose(file);
    }
}