#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatalogoVideogame.h"

//Funzione per la creazione del catalogo
void ScriviCatalogo(char *nomeFile){
    //Array dei 20 giochi iniziali 
    videogame_t catalogo[GIOCHI_START]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, {"Avventura", "", "", "", ""}, {{-1,""}}, 0},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, {"Azione", "", "", "", ""}, {{-1,""}}, 0},
        {"God of War", "Sony", "Santa Monica Studio", "Mitologia nordica reinventata", 2018, {"Azione", "Avventura", "GDR", "", ""}, {{-1,""}}, 0},
        {"Super Mario Odyssey", "Nintendo", "Nintendo EPD", "", 2017, {"Platform", "", "", "", ""}, {{-1,""}}, 0},
        {"Hollow Knight", "Team Cherry", "Team Cherry", "Metroidvania atmosferico", 2017, {"Platform", "", "", "", ""}, {{-1,""}}, 0},
        {"Celeste", "Matt Makes Games", "Matt Makes Games", "", 2018, {"Platform", "", "", "", ""}, {{-1,""}}, 0},
        {"Dark Souls III", "Bandai Namco", "FromSoftware", "Sfida hardcore fantasy", 2016, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Elden Ring", "Bandai Namco", "FromSoftware", "Open-world soulslike", 2022, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Minecraft", "Mojang", "Mojang Studios", "Costruisci e sopravvivi in mondi infiniti", 2011, {"Sandbox", "Costruzione", "Survival", "", ""}, {{-1,""}}, 0},
        {"Stardew Valley", "ConcernedApe", "ConcernedApe", "Fattoria e vita rurale", 2016, {"Simulazione", "", "", "", ""}, {{-1,""}}, 0},
        {"Hades", "Supergiant Games", "Supergiant Games", "", 2020, {"Roguelike", "", "", "", ""}, {{-1,""}}, 0},
        {"DOOM Eternal", "Bethesda", "id Software", "Spara e distruggi demoni", 2020, {"Sparatutto", "", "", "", ""}, {{-1,""}}, 0},
        {"Overwatch", "Blizzard", "Blizzard", "FPS a squadre", 2016, {"Sparatutto", "", "", "", ""}, {{-1,""}}, 0},
        {"Cyberpunk 2077", "CD Projekt", "CD Projekt RED", "Futuro distopico open-world", 2020, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Animal Crossing: New Horizons", "Nintendo", "Nintendo EPD", "", 2020, {"Simulazione", "", "", "", ""}, {{-1,""}}, 0},
        {"Among Us", "Innersloth", "Innersloth", "Deduzione sociale spaziale", 2018, {"Party", "", "", "", ""}, {{-1,""}}, 0},
        {"Fortnite", "Epic Games", "Epic Games", "Battle royale cartoonesco", 2017, {"Battle Royale", "", "", "", ""}, {{-1,""}}, 0},
        {"League of Legends", "Riot Games", "Riot Games", "", 2009, {"MOBA", "", "", "", ""}, {{-1,""}}, 0},
        {"Tetris", "Nintendo", "Alexey Pajitnov", "", 1984, {"Puzzle", "", "", "", ""}, {{-1,""}}, 0}
    };
    //Inizializza tutte le recensioni a -1 per ogni gioco
    for (short i=0; i<GIOCHI_START; i++) {
        for (short j=0; j<MAX_RECENSIONI; j++) {
            catalogo[i].recensione[j].recensione_num=-1;
            strcpy(catalogo[i].recensione[j].recensione_scritta, "");
        }
    }

    //Verifica se il file esiste già
    FILE* file=fopen(nomeFile, "rb"); //Se il file è apribile in rb allora già esiste, bisogna non entrarci
    if(file==NULL){ 
        short flag=1; //Controllare se il file è stato creato correttamente
        file=fopen(nomeFile, "wb");
        if(file!=NULL){
            if(fwrite(catalogo, sizeof(videogame_t), GIOCHI_START,file)!=GIOCHI_START) flag=0; // Controlliamo che scriva tutti gli elementi definiti dal numero della costante
            if(!flag) printf("\nErrore nella scrittura");
            else printf("\nDatabase inizializzato!\n");
            fclose(file);
        }
        else printf("\nError\n");
    }
    else{
        //Il file esiste già, non dobbiamo riscriverlo
        //printf("\nFile gia' esistente");
        fclose(file);
    }
}