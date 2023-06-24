#ifndef estructuras_h
#define estructuras_h

typedef struct List List;
typedef struct HashMap HashMap;

typedef struct act{
  int vida;
  int fuerza;
  List* itemBorrar;
} act;

typedef struct res{
  int opcion;
  int fuerzaNecesaria;
  int vidaNecesaria;
} res;

typedef struct Node{
  char ID[10];
  char TipoHistoria[10];
  FILE *Historia;
  //List *sucesos;
  act accion;
  int cantNodos;
  res restriccion;
  List* adjNode;  
} Node;

typedef struct Grafo{
  HashMap *nodos;
} Grafo;

typedef struct estadisticas{
  int fuerza;
  int salud;
}estadisticas;

typedef struct inve{
  char item[21];
} inve;

typedef struct jugador{
  char nombre[10];
  inve *inventario;
  estadisticas stats;
} jugador;

Grafo* createGrafo();

void agregarNodo(Grafo *grafo, Node *n);

void registrar(jugador *a, char *name);

#endif