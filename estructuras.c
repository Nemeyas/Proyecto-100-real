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

void registrar(jugador *a, char *name){
  a = (jugador*)malloc(sizeof(jugador));
  strcpy(a -> nombre, name);
  a->inventario = (inve*)malloc(2 * sizeof(inve)); 
  a->stats.fuerza = 0; 
  a->stats.salud = 20; 
}