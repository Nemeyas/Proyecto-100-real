#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "estructuras.h"
#include "gotoxy.h"
#include "hashmap.h"
#include "list.h"
#include "importar.h"
#include "fight.h"
#define Barra "------------"
#define BARRA "-------------------------------------------------------"

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
    for(int i=0; i<nodo->cantNodos;i++){
      gotoxy(0,29+i*3); printf("    %s", nodo->adjNode[i]);
    }
    while(true){
      Sleep(200);
      limpiarFlecha(0, 29, nodo->cantNodos);
      ubicarFlecha(0, 29, option);
      if(cambiarOpcion(&option,nodo->cantNodos)) break;
    }

    char *codigoSiguienteNodo = nodo->adjNode[option];
    no2 = searchMap(g->nodos,codigoSiguienteNodo);
    
    //system("pause");
    if(ValidarNodo(no2, player)){
      break;
    }

  }while(true);
  return no2;
}
//hasta aqui

void mostrarMenu(Grafo *g,Node *n, jugador *p){
  int option=0;
  while(true){
    GetAllKeys();
    system("cls");

    printf("  \n");
    printf("__________ ____ ________________   ____ ___________ __________________     _____ _____________________ \n");
    printf("\\______   \\    |   \\_   ___ \\   \\ /   / \\_   _____//   _____/\\_   ___ \\   /  _  \\\\______   \\_   _____/ \n");
    printf(" |     ___/    |   /    \\  \\/\\   Y   /   |    __)_ \\_____  \\ /    \\  \\/  /  /_\\  \\|     ___/|    __)_  \n");
    printf(" |    |   |    |  /\\     \\____\\     /    |        \\/        \\\\     \\____/    |    \\    |    |        \\ \n");
    printf(" |____|   |______/  \\______  / \\___/    /_______  /_______  / \\______  /\\____|__  /____|   /_______  / \n");
    printf("                           \\/                   \\/        \\/         \\/         \\/                 \\/  \n");
    printf("       _________.___   _____   ____ ___.____       ________________________ __________                 \n");
    printf("      /   _____/|   | /     \\ |    |   \\    |     /  _  \\__    ___/\\_____  \\\\______   \\                \n");
    printf("      \\_____  \\ |   |/  \\ /  \\|    |   /    |    /  /_\\  \\|    |    /   |   \\|       _/                \n");
    printf("      /        \\|   /    Y    \\    |  /|    |___/    |    \\    |   /    |    \\    |   \\                \n");
    printf("     /_______  /|___\\____|__  /______/ |_______ \\____|__  /____|   \\_______  /____|_  /                \n");
    printf("             \\/             \\/                 \\/       \\/                 \\/       \\/                 \n");
                                                                                            
    gotoxy(0,27);puts(BARRA);
    gotoxy(0,28);printf("\n");
    gotoxy(6,29);printf("Comenzar\n");
    gotoxy(0,30);puts(BARRA);
    gotoxy(6,31);printf("\n");
    gotoxy(6,32);printf("Cargar Partida\n");
    gotoxy(0,33);puts(BARRA);
    gotoxy(6,34);printf("\n");
    gotoxy(6,35);printf("Salir\n");
    gotoxy(0,36);puts(BARRA);
    while(true){
      limpiarFlecha(0, 29, 3);
      ubicarFlecha(0, 29, option);
      if(cambiarOpcion(&option, 3)) break;
    }
    switch (option){
      case 0: 
        return; //Salir del menu
      case 1:
        subrutina(g,n,p);
        break; //Realizar subrutinas dentro del mismo menu
      case 2: 
        system("cls");
        printf("Adios");
        exit(0); //Salir del programa
    } 
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

char leerNombre(char *nombre){
  int largoName;

  printf("Ingrese el nombre del jugador\n");
  scanf(" %[^\n]", nombre);
  largoName = strlen(nombre);
      
  while (largoName > 15 || largoName < 1) {
    printf("Ingrese un nombre valido (hasta 15 caracteres)\n");
    scanf(" %[^\n]", nombre);
    largoName = strlen(nombre);
  }

  return *nombre;
}

jugador* registrar(){
  char name[20];
  leerNombre(name);
  jugador *player = (jugador*) malloc (sizeof(jugador));
  strcpy(player->nombre, name);
  player->size = 0;
  player->inventario = (inve*) malloc (2 * sizeof(inve)); 
  player->stats.fuerza = 0; 
  player->stats.salud = 20; 
  return player;
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

void SioNo(){
  int option=0;
  GetAllKeys();
  while(true){
    system("cls");
    gotoxy(6, 0);printf("Estas seguro de que quieres salir del juego? Se perdera todo el progreso no guardado");
    gotoxy(6, 3);printf("Si");
    gotoxy(6, 6);printf("No");
    while(true){
      limpiarFlecha(0, 3, 2);
      ubicarFlecha(0, 3, option);
      if(cambiarOpcion(&option, 2)) break;
    }
    switch (option){
      case 0: 
        system("cls");
        printf("Una pena te extrañaremos");
        exit(0);
      case 1:
        return;
    }
  }
}

void menuDelJuego(char *a, Node *n, Grafo *g, jugador *p){
  int option=0;
  int option2=0;
  char respuesta[20];
  GetAllKeys();
  while(true){
    system("cls");
    gotoxy(8, 0); printf("MENU DE PAUSA");
    gotoxy(6, 3); printf("Resumir");
    gotoxy(6, 6); printf("Reiniciar partida");
    gotoxy(6, 9); printf("Guardar Partida");
    gotoxy(6, 12); printf("Salir");
    while(true){
      limpiarFlecha(0, 3, 4);
      ubicarFlecha(0, 3, option);
      if(cambiarOpcion(&option, 4)) break;
    }
    switch (option){
      case 0: 
        system("cls");
        return; //Salir del menu
      case 1:
        system("cls");
        a= firstList(n->tiposHistorias);
        return;
      case 2:
        guardarPartida(g,n,p);
        break; //Realizar guardado de progreso
      case 3: 
        system("cls");
        SioNo(); //Salir del programa🗿
    } 
  }
}

int main(void) {
  int seleccion=0;
  int contador=0;
  int contador2 = 0;
  bool si = false;
  Node *nodoActual = NULL;
  jugador *player = NULL;
  
  Grafo* g = createGrafo();
  HashMap *enemies = createMap(30);
  importarArchivos(g, enemies, player, nodoActual);
  mostrarMenu(g, nodoActual, player);
  system("cls");
  if(player == NULL || nodoActual == NULL){
    nodoActual = (searchMap(g->nodos,"Comenzar la prueba"));
    player = registrar();
  }
  while(true){ //Actualizar nodos
    //printf("%c \n",176);
    //profe();
    //printf("%s ", nodoActual->ID);
    char *a = firstList(nodoActual->tiposHistorias);
    //printf("%s\n", a);
    //system("pause");
  while(true){ //Escribir historias
      if(GetAsyncKeyState(VK_ESCAPE)){
        menuDelJuego(a,nodoActual,g,player);
        contador2 = contador;
        a = firstList(nodoActual->tiposHistorias);
        system("cls");
        si = true;
        //printf(" %s ", a);
      }
      else if( si == true){
        if( contador2 == 0){
          a = prevList(nodoActual->tiposHistorias);
        } 
        else{
          for(int i = 0 ; i == contador2 ; i++){
            a = nextList(nodoActual->tiposHistorias);
          }
        }
      }
      else if(strcmp(a,"")==0){
        a=nextList(nodoActual->tiposHistorias);
        gotoxy(0,28);printf(" %s ", a);
        if(strcmp(a=nextList(nodoActual->tiposHistorias),"")==0){
          a=nextList(nodoActual->tiposHistorias);
          gotoxy(0,29);printf(" %s ", a);
          if(strcmp(a=nextList(nodoActual->tiposHistorias),"")==0){
            a=nextList(nodoActual->tiposHistorias);
            gotoxy(0,10);printf(" %s ", a);
          }
        }
        a = prevList(nodoActual->tiposHistorias);
        system("pause");
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
        //jugador *enemy = searchMap(enemies, nextList(nodoActual->tipoHistorias));
        //fight(player, enemy);
      }
      else if(strcmp(a,"choice")==0){
        break;
      }
      else if(strcmp(a, "End")==0){
        //creditos();
        return 0;
      }
      else{
        gotoxy(0,27);printf(" %s ", a);
      }
      a = nextList(nodoActual->tiposHistorias);
      if( si == true){
        a = prevList(nodoActual->tiposHistorias);
        si = false;
        contador--;
      }
      contador++;
    }
    contador = 0;
    nodoActual = seleccionador2(g, nodoActual, player);
  }
  return 0;
}

//hacerle registrar al player cuando se carga partida, quizas reservar espacio para el nodo tmb