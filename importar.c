#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "estructuras.h"
#include "hashmap.h"
#include "importar.h"

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

void importarDatos(Grafo *g, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[1024];
  char *aux;
  int i, CantNodos;
  fgets(linea, 1023, archivo);
  while(fgets(linea, 1023, archivo) != NULL){ //Se leen todas las lineas en orden
    Node *nodo = (Node *) malloc (sizeof(Node));
    for(i = 0 ; i < 9 ; i++){//Se realizan 7 ciclos para permitir que se realizen las suficientes operaciones(6 valores en el struct)
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
        if(strcmp(aux,"0"))
        strcpy(nodo->accion.itemBorrar, aux);
      }
      if(i == 4){
        nodo->restriccion.vidaNecesaria = atoi(aux);
      }
      if(i == 5){
        nodo->restriccion.fuerzaNecesaria = atoi(aux);
      }
      if(i == 6){
        if(strcmp(aux,"0"))
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
    printf("...%s...", nodo->ID);
    insertMap(g->nodos, nodo->ID, nodo);
  }
  fclose(archivo);
}

void importarLore(Grafo *g, char *archivoName){
  FILE *archivo = fopen(archivoName, "r");
  char linea[1024];
  char *aux;
  char aux2;
  int i, CantNodos;
  Node *nodo;
  while(fgets(linea, 1024, archivo) != NULL){
    for( int i = 0 ; i < 2 ; i++){
      aux = (char*)get_csv_field(linea, i,'.');
      if(i == 0 ){
        nodo = searchMap(g->nodos, aux);
        printf("...%s...", nodo->ID);
         printf("%s", aux);
      }
      if (i == 1){
        nodo->tiposHistorias = createList();
        int cantHistorias = atoi(aux);
        while (cantHistorias != 0){
          i++;
          aux = (char*)get_csv_field(linea, i,'.');
          char *historia = malloc(sizeof(char)*200);
          strcpy(historia, aux);
          pushBack(nodo->tiposHistorias, historia);
          cantHistorias--;
        }
      }
    }
  }
  fclose(archivo);
}

void importarArchivos(Grafo *g){
  importarDatos(g, "conexiones.csv");
  importarLore(g, "prueba.csv");
}
