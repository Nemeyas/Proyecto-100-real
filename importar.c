#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "estructuras.h"
#include "hashmap.h"
#include "importar.h"
#include "gotoxy.h"

const char *get_csv_field (char * tmp, int k, char del) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= del){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== del){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
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

void importarDatos(Grafo *g, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[1024];
  char *aux;
  int i, CantNodos;
  fgets(linea, 1023, archivo);
  while(fgets(linea, 1023, archivo) != NULL){ //Se leen todas las lineas en orden
    Node *nodo = (Node *) malloc (sizeof(Node));
    for(i = 0 ; i < 9 ; i++){//Se realizan 9 ciclos para permitir que se realizen las suficientes operaciones(6 valores en el struct)
      aux = (char*)get_csv_field(linea, i, ','); //aux se convierte en la linea de caracteres i-esima para rellenar el valor correspondiente.
      //ruta1. 2. ruta3. ruta4. 12. 32.
      if(i == 0){
        strcpy(nodo->ID, aux);
      }
      if(i == 1){
        nodo->accion.vida = atoi(aux);
      }
      if(i == 2){
        nodo->accion.fuerza = atoi(aux);
      }
      if(i == 3){
        strcpy(nodo->accion.itemBorrar, aux);
      }
      if(i == 4){
        nodo->restriccion.vidaNecesaria = atoi(aux);
      }
      if(i == 5){
        nodo->restriccion.fuerzaNecesaria = atoi(aux);
      }
      if(i == 6){
        strcpy(nodo->restriccion.itemNecesario,aux);
      }
      if(i == 7){ 
        CantNodos = atoi(aux);
        nodo->cantNodos = CantNodos;
      } 
      if(i == 8){
        for(int a = 0; a < CantNodos; a++){
          char *aux2=(char*)get_csv_field(linea, a+i,',');
          if(aux2 != NULL) strcpy(nodo->adjNode[a],aux2);
        }
      }
    }
    //printf("...%s...", nodo->ID);
    insertMap(g->nodos, nodo->ID, nodo);
  }
  fclose(archivo);
}

void importarLore(Grafo *g, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[2500];
  char *aux;
  int i, CantNodos;
  Node *nodo;
  while(fgets(linea, 2499, archivo) != NULL){
    for( int i = 0 ; i < 2 ; i++){
      aux = (char*)get_csv_field(linea, i,'.');
      if(i == 0 ){
        nodo = searchMap(g->nodos, aux);
        /*printf("...%s...", nodo->ID);
         printf("%s", aux);*/
      }
      if (i == 1){
        nodo->tiposHistorias = createList();
        int cantHistorias = atoi(aux);
        while (cantHistorias != 0){
          i++;
          aux = (char*)get_csv_field(linea, i,'.');
          char *historia = malloc(sizeof(char)*1700);
          strcpy(historia, aux);
          pushBack(nodo->tiposHistorias, historia);
          cantHistorias--;
        }
      }
    }
  }
  fclose(archivo);
}

void importarEnemigos(HashMap *enemies, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[1024];
  char *aux;
  int i;
  fgets(linea, 1023, archivo);
  while(fgets(linea, 1023, archivo) != NULL){ //Se leen todas las lineas en orden
    enemigo *enemy = (enemigo *) malloc (sizeof(enemigo));
    for(i = 0 ; i < 3 ; i++){
      aux = (char*)get_csv_field(linea, i, ','); //aux se convierte en la linea de caracteres i-esima para rellenar el valor correspondiente.
      if(i == 0){
        strcpy(enemy->nombre, aux);
      }
      if(i == 1){
        enemy->stats.salud = atoi(aux);
      }
      if(i == 2){
        enemy->stats.fuerza = atoi(aux);
      }
    }
    insertMap(enemies, enemy->nombre, enemy);
  }
  fclose(archivo);
}

/*
void importarImagen(Grafo *g, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[1024];
  char *aux;
  int i, CantNodos;
  Node *nodo;
  while(fgets(linea, 1024, archivo) != NULL){
    for( int i = 0 ; i < 2 ; i++){
      aux = (char*)get_csv_field(linea, i,'.');
      if(i == 0){
        nodo = searchMap(g->nodos, aux);
        printf("...%s...", nodo->ID);
         printf("%s", aux);
      }
      if (i == 1){
        int tamanio = 25;
        while (tamanio != 0){
          i++;
          aux = (char*)get_csv_field(linea, i,',');
          char *imagen = malloc(sizeof(char));
          strcpy(imagen, aux);
          pushBack(nodo->imagenes, imagen);
          tamanio--;
        }
      }
    }
  }
  fclose(archivo);
}*/

void importarSave(Grafo *g, Node *nodoActual, jugador *player){
  FILE *archivo = fopen("save.csv", "r");
  char linea[1024];
  char *aux;
  int i;
  fgets(linea, 1023, archivo);
  while(fgets(linea, 1023, archivo) != NULL){ //Se leen todas las lineas en orden
    for(i = 0 ; i < 4 ; i++){
      aux = (char*)get_csv_field(linea, i, ','); //aux se convierte en la linea de caracteres i-esima para rellenar el valor correspondiente.
      if(i == 0){
        nodoActual = searchMap(g->nodos, aux);
      }
      if(i == 1){
        strcpy(player->nombre, aux);
      }
      if(i == 2){
        player->stats.salud = atoi(aux);
      }
      if(i == 3){
        player->stats.fuerza = atoi(aux);
      }
      if(i == 4){
        player->size = atoi(aux);

        if (player->size != 0){
          for (int j = 0 ; j < player->size ; j++){
            i++;
            aux = (char*)get_csv_field(linea, i, ',');
            strcpy(player->inventario[j].item, aux);
          }
        }
      }
    }
  }
  fclose(archivo);
}


void subrutina(Grafo *g,Node *n, jugador *p){
  FILE *archivo = fopen("save.csv", "r");
  char linea[1024];
  char *aux;
  int i;
  int option=0;
  GetAllKeys();
  while(true){
    system("cls");
    if(verificarArchivo("save.csv")==0){
      printf("No hay partidas guardadas");
      system("pause");
      return;
    }
    gotoxy(6, 0);printf("Vas a continuar esta partida?");
    while(fgets(linea, 1023, archivo) != NULL){ //Se leen todas las lineas en orden
      for(i = 0 ; i < 2 ; i++){
        aux = (char*)get_csv_field(linea, i, ',');
        if(i==0){
          gotoxy(6,3);printf("Historia: %s", aux);
        }
        if(i==1){
          gotoxy(6,4);printf("Nombre: %s", aux);
        }
      }
    }
    gotoxy(6, 9);printf("Si");
    gotoxy(6, 12);printf("No");
    while(true){
      limpiarFlecha(0, 6, 2);
      ubicarFlecha(0, 9, option);
      if(cambiarOpcion(&option, 2)) break;
    }
    switch (option){
      case 0: 
        importarSave(g,n,p);
        printf("Partida cargada con exito");
        gotoxy(6,20);printf(" ..%s...",p->nombre);
        gotoxy(6,21);printf(" ......%s...",n->ID);
        system("pause");
        return;
      case 1:
        printf("Y pa que entraste?\n");
        system("pause");
        system("cls");
        return;
    }
  }
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

void guardarPartida(Grafo *g,Node *n, jugador *p){
  int option=0;
  GetAllKeys();
  while(true){
    system("cls");
    gotoxy(6, 0);printf("Estas seguro de esto? Se sobreescribiran los datos anteriores");
    gotoxy(6, 3);printf("Si");
    gotoxy(6, 6);printf("No");
    while(true){
      limpiarFlecha(0, 3, 2);
      ubicarFlecha(0, 3, option);
      if(cambiarOpcion(&option, 2)) break;
    }
    switch (option){
      case 0: 
        save(g,n,p);
        printf("Partida guardada");
        system("pause");
        return;
      case 1:
        printf("Y pa que entraste?\n");
        system("pause");
        system("cls");
        return;
    }
  }
}

void importarArchivos(Grafo *g, HashMap *enemies, jugador *player, Node *nodoActual){
  importarDatos(g, "conexiones.csv");
  importarLore(g, "prueba.csv");
  importarEnemigos(enemies, "enemy.csv");
  //importarImagen(g, "imagenes.csv");

}
