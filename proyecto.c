#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "estructuras.c"
#include "gotoxy.h"
#include "importar.c"
//#include "fight.c"
#include "hashmap.h"
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
    gotoxy(10, 11); printf("SLOT %");
    gotoxy(10, 12); system("pause");
}

int seleccionador(int i){
  int option = 0;
  GetAllKeys();
  
  while(true){
    limpiarFlecha(0, 3, i);
    formatearOpcion(&option, i);
    ubicarFlecha(0, 3, option);
    if(cambiarOpcion(&option)) break;
  }

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
  fopen("historia.csv", "r");
  importar(g, "historia.csv");
  Node *nodoActual= firstMap(g->nodos);
  Pair *a=firstMap(nodoActual);
  jugador *player;

  char nombre[16];
  leerNombre(nombre);
  registrar(player, nombre);
  
  while(true){
    int a = nodoActual->cantNodos;
    if(strcmp(nodoActual->TipoHistoria,'pause')){
      printf(a);
      system('pause');
    }
    if(strcmp(nodoActual->TipoHistoria,"fight")){
      jugador *enemy = leerEnemigo(enemy);
      fight(enemy, player);
    }
    if(strcmp(nodoActual->TipoHistoria,'choice')){
      seleccionador(a);
    }
    else{
      printf(a);
    }
    a=nextMap(g -> nodos );
  }
  
  /*GetAllKeys();
  ocultarCursor();
  mostrarMenu();
  subirNivel();
  agregarItem();
  InventarioSUB();*/

  return 0;
}