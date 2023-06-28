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

void ubicarFlecha(int x, int y, int opcion){
    gotoxy(x, y + opcion*3);
    printf("-->");
}

bool cambiarOpcion(int * opcion, int cantOpciones){
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
   
    if(*opcion < 0) *opcion = cantOpciones + *opcion;
    *opcion = *opcion % cantOpciones;
    return false;
}

void subrutina(){
    GetAllKeys();
    system("cls");
    gotoxy(10, 10); printf("Partidas guardadas");
    gotoxy(10, 11); printf("SLOT ");
    gotoxy(10, 12); system("pause");
}

bool ValidarNodo(Node *n, jugador *player){
  if(player->stats.salud < n->restriccion.vidaNecesaria){
      system("cls");
      printf("Podrias morir si haces esto\n");
      system("pause");
      return false;
  }
  if(player->stats.fuerza < n->restriccion.fuerzaNecesaria){
    system("cls");
    printf("No tienes la fuerza necesaria para hacer esto\n");
    system("pause");
    return false;
  }
  if(strcmp(n->restriccion.itemNecesario,"0")==0){
    system("cls");
    return true;
  } 
  for(int i=0; i<player->size; i++){
    if(strcmp(player->inventario[i].item,n->restriccion.itemNecesario) == 0){
      system("cls");
      return true;
    } 
  }
  printf("No tienes el item %s necesario para esta accion\n", n->restriccion.itemNecesario);
  system("pause");
  system("cls");
  return false;
}

Node *seleccionador2(Grafo*g, Node* nodo, jugador* player){
  Node *no2 = NULL;
  do{
    int option = 0;
    GetAllKeys();
    //printf("%i",nodo->cantNodos);
    for(int i=0; i<nodo->cantNodos;i++){
      gotoxy(0,3+i*3); printf("    %s", nodo->adjNode[i]);
    }
    while(true){
      Sleep(250);
      limpiarFlecha(0, 3, nodo->cantNodos);
      ubicarFlecha(0, 3, option);
      if(cambiarOpcion(&option,nodo->cantNodos)) break;
    }

    char *codigoSiguienteNodo = nodo->adjNode[option];
    //system("cls");
    //printf("...%s...\n", codigoSiguienteNodo);
    no2 = searchMap(g->nodos,codigoSiguienteNodo);
    //printf("....%s....", no2->ID);
    //printf("%s ", no2->ID);
    /*char *a = firstList(no2->tiposHistorias);
    while (a){
       printf("%s\n", a);
       a=nextList(no2->tiposHistorias);
    }
    
    system("pause");*/
    if(ValidarNodo(no2, player)){
      break;
    }

  }while(true);
  return no2;
}
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
      ubicarFlecha(0, 3, option);
      if(cambiarOpcion(&option, 3)) break;
    }
    switch (option){
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
  //jug->size++;
  //jug->inventario = realloc(jug->size, sizeof(char));

  for (int i = 0; i < jug->size; i++){
    if(jug->inventario[i].item == NULL){
      strcpy(jug->inventario[i].item,nombreItem);
      printf("sexo online correcto\n");
      return;
    }
  }
  printf("El inventario esta lleno. No se puede agregar el item '%s'.\n", nombreItem);
}

void InventarioSUB(jugador *jug, int incremento) {
  int nuevoTamano = incremento;
  jug->inventario = (inve*)realloc(jug->inventario, nuevoTamano * sizeof(inve));
}

void profe(){
  printf("░░░░░░░░░░░░░░░█████████████████████░░░░░░░░░░░░░░░░░░░███████████████████░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░░███████████████████░░░░░░░░░░░░░░░░░░░░░░░████████████████████░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█████████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█████████████████░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░██████████████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░████████████░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░██████████░░░░░░░░░█████░░░░░░░░░░░░░░░░░░██████░░░░░░░░░░███████░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█████░░░░░░░░░░░░███░░░░███░░░░░░░░░░░░░░██░░░░██░░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░░░░░░░░██░░░░██████░░░░░░░░░░░██░░░██████░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░░░░░░░░██░░█████████░████████░█░░░███████░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░███████████████████░░████████████░░░░░░███░█████████████████████████░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░░█░░░░░░░░░░░░░░█████████████░░░░░░░░░░███████████░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░██░░░░░░░░░░░░░░█████████████░░░░░░░░░░███████████░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░████████████░░░░░░█░░░███████████░░░░░░░░░░░░░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░███████████░░░░░░░█░░░██████████░░░░░░░░░░░░░███░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░█████████░░░░░░░░██░░░░███████░░░░░░░░░░░███░░█░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░███░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░░░░░███░░██░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░████░░░░░░░░░░░░░░░░░░░░█░░░░░░░█░░░░░░░░░░░░░░░░░░████░░░█░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░████░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░███░░█░░░█░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░█████░░░░░▄▀░░░░░░░░░░░░░░░░░░░░░░▀█▄░░░░░░████░░░█░░░░█░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░█░░░███░░░░░░░░░░█░░░░░░░░░░█▄░░░░░░▀██████░█░░░██░░░░█░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░█░░░░░░░░██░░█░████░░░░░▐▀░░░░░░░░░░░░░▀▄░░░░███░█░░░█░░░█░░░░░█░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░░██░░░░░░░░██░██░░░░█████░░░░░░░░░░░░░░░░░░░███░░░█░░██░░█░░░░░██░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░░████░░░░░░░░██░█░░░░█░░░░████████████████████░░░░░█░░█░░█░░░░░██░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░██████░░░░░░░░███░░░░█░░░░░░░░░░█░░░░░█░░░░░░█░░░░░█░░███░░░░██░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░░███░██░░░░░░░░░░███░░█░░░░░░░░░░█░░░░░█░░░░░░█░░░░█░░░██░░░░██░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░░███░████░░░░░░░░░░░████░░░░░░░░░░█░░░░░█░░░░░░█░░░░████░░░░░██░░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░░███████████░░░░░░░░░░░░█████████░░█░░░░██░░░░░███████░░░░░░░██░░░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░░░█████████░░██░░░░░░░░░░░░░░░░░░░████████████████░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░░░\n");
  printf("░░░░░░█████░███░░░░░██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░░░░\n");
  printf("░░░░█████░████░░░░░░░██░░░░░░░░░░░░░░░░░░░░░░░░░█░░░░░░░░░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░\n");
  printf("░░████░░████░░░░░░░░░░███░░░░░░░░░░░░░░░░░░░█████████░░░░░░░░░░░░░██░░░░░░░░░░░░░░░░░░░░░\n");
}

void save(Grafo *g, Node* nodo){
  FILE *archivo = fopen("save.csv", "w");
  fprintf(archivo, "%s", nodo->ID);
  fclose(archivo);
}

int verificarArchivo(const char* nombreArchivo) {
  FILE* archivo = fopen(nombreArchivo, "r");

  fseek(archivo, 0, SEEK_END);
  long tamano = ftell(archivo);

  if (tamano == 0) {
    fclose(archivo);
    return 0;
  }

  fclose(archivo);
  return 1;
}

int main(void) {
  int seleccion=0;
  Grafo* g = createGrafo();
  importarArchivos(g);
  mostrarMenu();
  system("cls");
  Node *nodoActual = (searchMap(g->nodos, "ruta1"));
  //Pair *a=firstMap(nodoActual);
  char nombre[16];
  int largoName;

  printf("Ingrese el nombre del jugador\n");
  scanf(" %[^\n]", nombre);
  largoName = strlen(nombre);
      
  while (largoName > 15 || largoName < 1) {
    printf("Ingrese un nombre valido (hasta 15 caracteres)\n");
    scanf(" %[^\n]", nombre);
    largoName = strlen(nombre);
  }

  //leerNombre(nombre);
  jugador *player = registrar(nombre);
  //agregarItem(player, "llave");
  //printf("%s \n%s ", player->nombre,  player->inventario[0]);

  

  while(true){ //Actualizar nodos
    //printf("%c \n",176);
    //profe();
    //printf("%s ", nodoActual->ID);
    char *a = firstList(nodoActual->tiposHistorias);
    //printf("%s\n", a);
    //system("pause");
    while(true){ //Escribir historias
      if(GetAsyncKeyState(VK_ESCAPE)){
        //menuDelJuego();
      }
      else if(strcmp(a,"name")==0){
        printf("%s", player->nombre);
      }
      else if(strcmp(a,"pause")==0){
        printf("\n\n\n ");
        system("pause");
        system("cls");
      }
      else if(strcmp(a,"fight")==0){
        //jugador *enemy = leerEnemigo(enemy);
        //fight(enemy, player);
      }
      else if(strcmp(a,"choice")==0){
        
        break;
      }
      else if(strcmp(a, "End")==0){
        //funcionFinal();
        return 0;
      }
      else if(strcmp(a,"")==0){
        printf("\n");
      }
      else{
        printf(" %s ", a);
      }
      a = nextList(nodoActual->tiposHistorias);
    }
    nodoActual = seleccionador2(g, nodoActual, player);
  }

  //--------------//
  //nodoActual = seleccionador(g->nodos, nodoActual, player);
  //a=nextMap(g -> nodos );

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

esto en el pseint no pasaba :v
sexo online porfavor
visual qlo me tiene los huevos hinchados wn, pseint good y el resto de weas son una mierda uwu
se actualiza al nodo actual
don omar
*/