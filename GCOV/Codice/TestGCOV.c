#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "unity_internals.h"
#include "CatalogoVideogame.h"

//Si definisce una costante per il nome del file di test, un catalogo test in modo da poter provare le operazioni
#define NOME_FILE_TEST "CatalogoTest.dat"

void setUp(){
    // This function is called before each test case.
    // You can use it to set up any necessary state or resources.
    remove(NOME_FILE_TEST);
}

void tearDown(){
    // This function is called after each test case.
    // You can use it to clean up any resources or state.
    remove(NOME_FILE_TEST);
}

//Prototipi delle funzioni di test 
void TestScritturaFile(void); 
void TestStasticaRecensione(void);
void TestStatisticheCopieVendute(void);
void TestCancellaGioco(void);

int main(void){
    UNITY_BEGIN();
    RUN_TEST(TestScritturaFile);
    RUN_TEST(TestStasticaRecensione);
    RUN_TEST(TestStatisticheCopieVendute);
    RUN_TEST(TestCancellaGioco);
    return UNITY_END();
}

//Test per verificare la corretta scrittura su file.
void TestScritturaFile(void){
    videogame_t giochi_test[]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, {"Avventura", "", "", "", ""}, {{-1,""}}, 0},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, {"Azione", "", "", "", ""}, {{-1,""}}, 0},
    };

    FILE *file=fopen(NOME_FILE_TEST,"wb");

    //Si controlla che il puntatore al file non sia nullo, indicando che l'apertura è riuscita.
    TEST_ASSERT_NOT_NULL(file);
    fwrite(giochi_test,sizeof(videogame_t),3,file);
    fclose(file);
}

//Test per la funzione StatisticaRecensione.
void TestStasticaRecensione(void){
    videogame_t giochi_test[]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, {"Avventura", "", "", "", ""}, {{-1,""}}, 0},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, {"Azione", "", "", "", ""}, {{-1,""}}, 0},
    };
    FILE *file=fopen(NOME_FILE_TEST,"wb");
    TEST_ASSERT_NOT_NULL(file);
    fwrite(giochi_test,sizeof(videogame_t),3,file);

    //Impostiamo manualemente delle recensioni numeriche, aspettandoci in ritorno un valore di 4
    for (int i=0; i<MAX_RECENSIONI; i++) giochi_test[0].recensione[i].recensione_num = -1;
    giochi_test[0].recensione[0].recensione_num=5; 
    giochi_test[0].recensione[1].recensione_num=3;
    giochi_test[0].recensione[2].recensione_num=4;

    float media=StatisticaRecensione(NOME_FILE_TEST, "The Legend of Zelda: Breath of the Wild", giochi_test[0]);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, media);
   
    fclose(file);
}

// Test per la funzione StatisticaCopieVendute.
void TestStatisticheCopieVendute(void){
    videogame_t giochi_test[]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, {"Avventura", "", "", "", ""}, {{-1,""}}, 0},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, {"Azione", "", "", "", ""}, {{-1,""}}, 0},
    };
    FILE *file=fopen(NOME_FILE_TEST,"wb");
    TEST_ASSERT_NOT_NULL(file);
    fwrite(giochi_test,sizeof(videogame_t),3,file);

    //Impostiamo manualmente le copie vendute per il secondo gioco.
    giochi_test[1].copie_vendute=60;
    
    float rapporto=StatisticaCopieVendute(NOME_FILE_TEST, "The Witcher 3: Wild Hunt", giochi_test[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.6f, rapporto);

    fclose(file);
}

// Test per la funzione CancellaGioco.
void TestCancellaGioco(void){
    videogame_t giochi_test[]={
        {"The Legend of Zelda: Breath of the Wild", "Nintendo", "Nintendo EPD", "Avventura open-world in Hyrule", 2017, {"Avventura", "", "", "", ""}, {{-1,""}}, 0},
        {"The Witcher 3: Wild Hunt", "CD Projekt", "CD Projekt RED", "Caccia mostri in un mondo fantasy", 2015, {"GDR", "", "", "", ""}, {{-1,""}}, 0},
        {"Red Dead Redemption 2", "Rockstar Games", "Rockstar Studios", "", 2018, {"Azione", "", "", "", ""}, {{-1,""}}, 0},
    };
    FILE *file=fopen(NOME_FILE_TEST,"wb");
    fwrite(giochi_test,sizeof(videogame_t),3,file);
    fclose(file);

    CancellaGioco(NOME_FILE_TEST, "The Witcher 3: Wild Hunt", giochi_test[1], 1);

    file=fopen(NOME_FILE_TEST, "rb");
    videogame_t gioco_letto;
    int conteggio=0;
    //Leggiamo tutti i record rimasti nel file.
    while(fread(&gioco_letto, sizeof(videogame_t), 1, file) == 1){
        conteggio++;
        //Controlliamo che nessuno dei record rimasti abbia il nome del gioco cancellato.
        TEST_ASSERT_TRUE(strcmp("The Witcher 3: Wild Hunt", gioco_letto.nome)!=0);
    }
    fclose(file);
    TEST_ASSERT_EQUAL_INT(2, conteggio);
}