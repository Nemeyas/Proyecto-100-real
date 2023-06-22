#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "hashmap.h"

typedef struct List List;

typedef struct {
  int vida;
  int fuerza;
  List* itemBorrar;
} act;

typedef struct {
  int opcion;
  int fuerzaNecesaria;
  int vidaNecesaria;
} res;

struct Node{
  char ID[10];
  char TipoHistoria[10];
  FILE *Historia;
  //List *sucesos;
  //act accion;
  int cantNodos;
  res restriccion;
  List* adjNode;  
};

typedef struct{
  int fuerza;
  int salud;
}estadisticas;

typedef struct{
  char item[21];
} inve;

typedef struct{
  char nombre[10];
  inve *inventario;
  estadisticas stats;
} jugador;

typedef struct{
  HashMap *nodos;
} Grafo;

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