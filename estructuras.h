#ifndef estructuras_h
#define estructuras_h

typedef struct List List;
typedef struct HashMap HashMap;

typedef struct {
  int vida;
  int fuerza;
  List* itemBorrar;
}act;

typedef struct res{
  int opcion;
  int fuerzaNecesaria;
  int vidaNecesaria;
}res;

typedef struct Node{
  char ID[25];
  char TipoHistoria[1300];
  List * tiposHistorias; //pushback("Historia 1"), pushback("Historia 2")
  act accion;
  int cantNodos;
  res restriccion;
  char adjNode[4][25]; //Segun la opción ecogida se recorre la lista tantas veces como lo que indique la opción  
}Node;

typedef struct estadisticas{
  int fuerza;
  int salud;
}estadisticas;

typedef struct inve{
  char item[21];
  int size;
}inve;

typedef struct jugador{
  char nombre[10];
  inve *inventario;
  estadisticas stats;
}jugador;

typedef struct Grafo{
  HashMap *nodos;
}Grafo;

Grafo * createGrafo();

void agregarNodo(Grafo *grafo, Node *n);

void registrar(jugador *a, char *name);

#endif