#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "estructuras.c"

/*void exportar(FILE *archivo){
  
  fprintf(archivo, "Nombre,Apellido,Edad,Teléfono,Dirección,Num Seguridad Social,Médicos\n");
  for(paciente *p = firstList(l) ; p != NULL; p = nextList(l)){
    //aqui pone todos los datos del struct menos medicos
    fprintf(archivo, "%s,%s,%d,%s,%s,%s\n", p->nombre,p->apellido,p->edad,p->telefono, p->direccion, p->numeroSocial);
    //aqui pone la lista de medicos
    for(char* a = firstList(p->medicos) ; a != NULL ; a = nextList(p->medicos)){
      fprintf(archivo, "%s", a);
      if(nextList(p->medicos) != NULL){
        fprintf(archivo,"; ");
      }
      else{
        fprintf(archivo, "\n");
      }
    }
  }
  fclose(archivo);
}*/

const char *get_csv_field (char * tmp, int k) {
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

        if(open_mark || tmp[i]!= '.'){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== '.'){
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

void escribir(FILE *Historia, char *aux){


}

void importar(Grafo *g,FILE *archivo){
  char linea[1300];
  char *aux;
  int i, CantNodos;
  while(fgets(linea, 1024, archivo) != NULL){ //Se leen todas las lineas en orden
    Node *nodo = (Node *) malloc (sizeof(Node));
    for(i = 0 ; i < 7 ; i++){//Se realizan 7 ciclos para permitir que se realizen las suficientes operaciones(6 valores en el struct)
      if (i != 6) aux = get_csv_field(linea, i); //aux se convierte en la linea de caracteres i-esima para rellenar el valor correspondiente.
      if(i == 0){
        strcpy(nodo->ID, aux);
      }
      if(i == 1){
        strcpy(nodo->TipoHistoria, aux);
      }
      if(i == 2){ 
        CantNodos= atoi(aux);
        nodo->cantNodos = CantNodos;
      }
      if(i == 3){
        res *restricciones = (res *) malloc (sizeof(res));
        nodo->restriccion.opcion = atoi(aux);
      }
      if(i== 4){
        nodo->restriccion.fuerzaNecesaria = atoi(aux);
      }
      if(i == 5){
        nodo->restriccion.vidaNecesaria = atoi(aux);
      } 
      if(i == 6){
        FILE *Historia;
        fopen(Historia, "w");
        escribir(Historia, aux);
        nodo->Historia = Historia;
        fclose(Historia);
      }
    }
  }
  fclose(archivo);
}

void importarArchivos(){
  Grafo *grafo = createGrafo();
  FILE *archivo = fopen('sucesos.csv',"rt");
  if (archivo == NULL) {
  printf("* Error al abrir el archivo.\n");
  } else{
  importar(grafo, archivo);
  }
  FILE *archivo = fopen('restricciones.csv',"rt");
  if (archivo == NULL) {
  printf("* Error al abrir el archivo.\n");
  } else{
  importar(grafo, archivo);
  }
  FILE *archivo = fopen('acciones.csv',"rt");
  if (archivo == NULL) {
  printf("* Error al abrir el archivo.\n");
  } else{
  importar(grafo, archivo);
  }
  FILE *archivo = fopen('conexiones.csv',"rt");
  if (archivo == NULL) {
  printf("* Error al abrir el archivo.\n");
  } else{
  importar(grafo, archivo);
  }
  FILE *archivo = fopen('guardar.csv',"rt");
  if (archivo == NULL) {
  printf("* Error al abrir el archivo.\n");
  } else{
  importar(grafo, archivo);
  }
}