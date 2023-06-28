#ifndef estructuras_h
#define estructuras_h

typedef struct List List;
typedef struct HashMap HashMap;

typedef struct {
  int vida;
  int fuerza;
  char itemBorrar[30];
}act;

typedef struct res{
  int opcion;
  int fuerzaNecesaria;
  int vidaNecesaria;
  char itemNecesario[30];
}res;

typedef struct Node{
  char ID[100];
  List * tiposHistorias; //pushback("Historia 1"), pushback("Historia 2")
  act accion;
  int cantNodos;
  res restriccion;
  char adjNode[4][100]; //Segun la opción ecogida se recorre la lista tantas veces como lo que indique la opción
  List *imagenes;
}Node;

typedef struct estadisticas{
  int fuerza;
  int salud;
}estadisticas;

typedef struct inve{
  char *item;
}inve;

typedef struct jugador{
  char nombre[16];
  inve *inventario;
  int size;
  estadisticas stats;
}jugador;

typedef struct Grafo{
  HashMap *nodos;
}Grafo;

Grafo * createGrafo();

void agregarNodo(Grafo *grafo, Node *n);

jugador *registrar(char name[16]);

#endif