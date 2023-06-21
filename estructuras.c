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
}act;

typedef struct {
  int opcion;
  int fuerzaNecesaria;
  int vidaNecesaria;
} res;

typedef struct {
  char ID[10];
  char TipoHistoria[10];
  FILE *Historia;
  //List *sucesos;
  //act accion;
  int cantNodos;
  res restriccion;
  List* adjNode;  
} Node;

typedef struct{
  int fuerza;
  int salud;
}estadisticas;

typedef struct{
  char item[21];
}inve;

typedef struct{
  char nombre[10];
  inve *inventario;
  estadisticas stats;
}jugador;

typedef struct{
  HashMap *nodos;
}Grafo;

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

void registrar(Grafo *grafo, char *nombre){
  jugador *a = (jugador*)malloc(sizeof(jugador));
  strcpy(grafo -> nombre, nombre);
  a->inventario = (inve*)malloc(2 * sizeof(inve)); 
  a->stats.fuerza = 0; 
  a->stats.salud = 20; 
}

void subirNivel(estadisticas *stats, int opcion) {
  switch (opcion) {
    case 1:
      stats->salud += 10;
      printf("Tu salud se a incrementado en 10[u.a]");
      break;
    case 2:
      stats->fuerza += 5;
      printf("Tu fuerza se a incrementado en 5[u.a]");
      break;
  }
}

void agregarItem(jugador *jug, char *nombreItem) {
  int i;
  for (i = 0; i < 2; i++) {
    if (strcmp(jug->inventario[i].item, "") == 0) {
      strcpy(jug->inventario[i].item, nombreItem);
      printf("Se ha agregado el item '%s' al inventario.\n", nombreItem);
      return;
    }
  }
  
  printf("El inventario está lleno. No se puede agregar el item '%s'.\n", nombreItem);
}

void incrementarEspacioInventario(jugador *jug, int incremento) {
  int nuevoTamano = incremento;
  jug->inventario = (inve*)realloc(jug->inventario, nuevoTamano * sizeof(inve));
}

