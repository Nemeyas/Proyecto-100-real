#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "estructuras.h"
#include "gotoxy.h"
#include "fight.c"
#include "hashmap.h"
#include "list.h"
#include "importar.h"
#define Barra "------------"
#define BARRA "-------------------------------------------------------"

//funciones del Nemeyas, no tocar
void limpiarFlecha(int x, int y, int cantOpciones){
    for(int i = 0; i < cantOpciones; i++){
        gotoxy(x, y + i*3); 
        printf("   ");
    }
}

void formatearOpcion(int* opcion, int cantOpciones){
    *opcion = *opcion % cantOpciones;
    if(*opcion < 0) *opcion = 3 + *opcion;
}

void ubicarFlecha(int x, int y, int opcion){
    gotoxy(x, y + opcion*3);
    printf("-->");
}

bool cambiarOpcion(int * opcion){
    Sleep(250);
    if( GetAsyncKeyState(VK_UP) ){
        *opcion -= 1;
    }
    if( GetAsyncKeyState(VK_DOWN) ){
        *opcion += 1;
    }
    if( GetAsyncKeyState(VK_RETURN) ){
        return true;
    }
    return false;
}

void subrutina(){
    GetAllKeys();
    system("cls");
    gotoxy(10, 10); printf("Partidas guardadas");
    gotoxy(10, 11); printf("SLOT ");
    gotoxy(10, 12); system("pause");
}

/*int seleccionador2(Grafo*g, Node* nodo, jugador* player){
  int option = 0;
  GetAllKeys();
  gotoxy(0,3);
  for(int i=0; i<nodo->cantNodos;i++){
    printf("  %s\n", nodo->adjNode[i]);
  }
  
  
  -->  Tomar un tenedor
  
  
  while(true){
    limpiarFlecha(0, 3, nodo->cantNodos);
    formatearOpcion(&option, nodo->cantNodos);
    ubicarFlecha(0, 3, option);
    if(cambiarOpcion(&option)) break;
  }

  //char codigoSiguienteNodo = nodo->adjNode[option];
  //nodo = searchMap(g->nodos,codigoSiguienteNodo);
  return 0;
}*/
//hasta aqui

void mostrarMenu(){
  int option=0;
  while(true){
    GetAllKeys();

    system("cls");

  puts(BARRA);
  printf("            PUCV PRISION ESCAPE SIMULATOR\n");
  puts(BARRA);
  printf("     Comenzar\n");
  puts(BARRA);
  printf("\n");
  printf("     Cargar Partida\n");
  puts(BARRA);
  printf("\n");
  printf("     Salir\n");
  puts(BARRA);
  while(true){
    limpiarFlecha(0, 3, 3);
    formatearOpcion(&option, 3);
    ubicarFlecha(0, 3, option);
    if(cambiarOpcion(&option)) break;
  }
  switch (option)
        {
        case 0: 
            return; //Salir del menu
        case 1:
            subrutina();
            break; //Realizar subrutinas dentro del mismo menu
        case 2: 
            system("cls");
            printf("Adios");
            exit(0); //Salir del programa
        } 
  }
}

void leerNombre(char *nombre){
  int largo = 0;
  printf("Ingrese su nombre de usuario (max. 15 caracteres)\n");

  while (largo <= 0 || largo > 15){
    scanf("%s", nombre);
    largo = strlen(nombre);
    if (largo > 15 || largo <= 0) printf("Ingrese un nombre valido (max. 15 caracteres)\n");
  }
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
      exit;
    }
  }
  printf("El inventario esta lleno. No se puede agregar el item '%s'.\n", nombreItem);
}

void InventarioSUB(jugador *jug, int incremento) {
  int nuevoTamano = incremento;
  jug->inventario = (inve*)realloc(jug->inventario, nuevoTamano * sizeof(inve));
}


int main(void) {
  int seleccion=0;
  Grafo* g = createGrafo();
  importarArchivos(g);

  Node* nodo1 = (Node *) malloc (sizeof(Node));
  strcpy(nodo1->ID,"nodo inicial");
  /*nodo1->TipoHistoria = createList();
  pushBack(nodo1->TipoHistoria,"hola\n");
  pushBack(nodo1->TipoHistoria,"pause");
  pushBack(nodo1->TipoHistoria,"como estan");
  pushBack(nodo1->TipoHistoria,"choice");
  nodo1->cantNodos = 2;
*/
  Node* nodo2 = (Node *) malloc (sizeof(Node));
  strcpy(nodo2->ID,"nodo 2");

  Node* nodo3 = (Node *) malloc (sizeof(Node));
  strcpy(nodo3->ID,"nodo 3");

  //strcpy(nodo1->adjNode[0],nodo2->ID);
  //strcpy(nodo1->adjNode[1],nodo3->ID);

  insertMap(g->nodos, nodo1->ID, nodo1);
  insertMap(g->nodos, nodo2->ID, nodo2);
  insertMap(g->nodos, nodo3->ID, nodo3);

  Node *nodoActual = (searchMap(g->nodos,"nodo inicial"));
  //Pair *a=firstMap(nodoActual);
  jugador *player;

  char nombre[16];
  leerNombre(nombre);
  registrar(player, nombre);
  
  while(true){ //Actualizar nodos
    while(true){ //Escribir historias

      if(strcmp(nodoActual->TipoHistoria,"pause")){
        printf(nodoActual->TipoHistoria);
        //system('pause');
      }
      if(strcmp(nodoActual->TipoHistoria,"fight")){
        //jugador *enemy = leerEnemigo(enemy);
        //fight(enemy, player);
      }
      if(strcmp(nodoActual->TipoHistoria,"choice")){
        break;
      }
      if(strcmp(nodoActual->TipoHistoria, "End")){
        //funcionFinal();
        return 0;
      }
    }
    //seleccionador2(g, nodoActual, player);
    //opcionEscogida = seleccionador(e)
    //codigoSiguienteNodo = nodoActual->adjNode[opcionEscogida];
    //nodoActual = searchMap(,codigoSiguienteNodo);

    //--------------//
    //nodoActual = seleccionador(g->nodos, nodoActual, player);
    //a=nextMap(g -> nodos );
  }
  
  /*GetAllKeys();
  ocultarCursor();
  mostrarMenu();
  subirNivel();
  agregarItem();
  InventarioSUB();*/

  return 0;
}

/*
while lectura de lista de historias {

habia una vez...
Luego sucedio....
fight....
pause
choice -> break;

}



seleccionador();{

--> nombreRuta Nodo1
    nombreRuta Nodo2
    nombreRuta Nodo3

verifica restricciónes
si pasa entonces,
se aplican acciones...
}



se actualiza al nodo actual