#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"
#include "estructuras.h"

Grafo* createGrafo(){
  HashMap *nodos = createMap(50);
  Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo->nodos = nodos;
  return grafo;
}

void agregarNodo(Grafo *grafo, Node *n){
  insertMap(grafo->nodos, n->ID, n);
  return;
}

jugador* registrar(char name[16]){
  jugador *player = (jugador*) malloc (sizeof(jugador));
  strcpy(player->nombre, name);
  player->inventario = (inve*) malloc (2 * sizeof(inve)); 
  player->stats.fuerza = 0; 
  player->stats.salud = 20; 
  player->size = 2;
  return player;
}

void creditos(){
  printf("             PUCV ESCAPE PRISION SIMULATOR\n");
  Printf()

}