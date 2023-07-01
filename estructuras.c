#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#include "estructuras.h"

Grafo* createGrafo(){
  HashMap *nodos = createMap(100);
  Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo->nodos = nodos;
  return grafo;
}

void agregarNodo(Grafo *grafo, Node *n){
  insertMap(grafo->nodos, n->ID, n);
  return;
}

void creditos(){
  printf("           PUCV ESCAPE PRISION SIMULATOR\n\n");
  printf("       ---------------CREDITOS------------------\n");
  printf("                      LOS GPT\n\n");
  printf("Sebastian Gatica\nMatias Castro\nAdolfo Cordero\nNehemias Leiva\nRuben Carvajal\n\n");
  printf("             Agradecimientos Especiales\n\n");
  printf("Joseph Donoso\nChat Gpt\nIgnacio Araya\nGuillermo Cabrera(Quien nos ensenio a programar)\nPseint(El mejor programa)\n");
  printf("Laura Griffiths\nFornite\nChoferes de la 903/902/901\nChoferes de la 101/102/103/104/106/107/108/109/110/111/112/113/114/115/610/611\nBuses: Via aeropuerto/Troncal sur\nMetro de Valparaiso(efe)");
  printf("Bajon del Compita, los mejores completos a $1700\nEl merluzo callampin bombin\nArturo Pratt\nSebastian Gatica\nMatias Castro\nAdolfo Cordero\nNehemias Leiva\nRuben Carvajal\n");
  printf("Planeta tierra\nCondore\nHuemul\nChinchillas\nLeones de Montania\nPudu\nPinguinos de Humboldt\nOxigeno\nPasos peatonales\nManuel\nBodoque\nRene Puente\nVendedor de lenia\n");
  printf("Huevito Rey\nBlue label\nFilmora\nJoseph Donoso\nChat Gpt\n\nARREGLEN LA VEREDA DEL CAPDUCAL que se forma el medio taco y llego tarde llevan 9 meses con la vola\n\n");
  printf("             Desagradecimientos\n\n");
  printf("Duende que nos boicoteaba el codigo\nGithub el cual simepre se buegeaba\n");
  system("pause");
  abort();
}