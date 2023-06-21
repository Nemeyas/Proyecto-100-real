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
  inve *inventario;
  estadisticas stats;
}jugador;

typedef struct{
  char nombre[10];
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

void subirNivel (estadisticas *stats){
  stats -> salud =+ 10; //se deberian pasar otros parametros, para comparar si quiere subir vida o fuerza
  stats -> fuerza =+ 5;
}