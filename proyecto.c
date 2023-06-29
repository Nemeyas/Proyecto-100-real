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
    Sleep(200);
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
    for(int i=0; i<nodo->cantNodos;i++){
      gotoxy(0,3+i*3); printf("    %s", nodo->adjNode[i]);
    }
    while(true){
      Sleep(200);
      limpiarFlecha(0, 3, nodo->cantNodos);
      ubicarFlecha(0, 3, option);
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

void save(Grafo *g, Node* nodo, jugador *player){
  FILE *archivo = fopen("save.csv", "w");
  fprintf(archivo, "%s,%s,%u,%u,%u", nodo->ID, player->nombre, player->stats.salud, player->stats.fuerza, player->size);

  if (player->size != 0){
    for (int i = 0 ; i < player->size ; i++){
      fprintf(archivo, ",%s", player->inventario[i].item);
    }
  }
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

void guardarPartida(){
  system("cls");
  
}

void SioNo(){
  int option=0;
  GetAllKeys();
  while(true){
    system("cls");
    gotoxy(10, 10);printf("Estas seguro de que quieres salir del juego?");
    gotoxy(10, 11);printf("Si");
    gotoxy(10, 12);printf("No");
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

void menuDelJuego(char *a, Node *n){
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
        guardarPartida();
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
  Grafo* g = createGrafo();
  HashMap *enemies = createMap(30);
  importarArchivos(g, enemies);
  mostrarMenu();
  system("cls");
  Node *nodoActual = (searchMap(g->nodos, "ruta1"));
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
        menuDelJuego(a, nodoActual);
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