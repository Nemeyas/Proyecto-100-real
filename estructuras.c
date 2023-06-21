#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct List List;

typedef struct {
  int vida;
  int fuerza;
  List* itemBorrar;
}act;

typedef struct Node {
  List *sucesos;
  //act accion;
  int cantNodos;
  //res restriccion;
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
  char nombre[31];
  List *nodos;
}Grafo;

Grafo* createGrafo(){
  Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
  grafo -> nodos = createList();
  return grafo;
}

void agregarNodo(Grafo *grafo, Node *n){
  pushBack(grafo->nodos, n);
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