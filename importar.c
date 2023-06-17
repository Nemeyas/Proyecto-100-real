#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

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

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
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

void importar(Grafo *g,FILE *archivo){
  char linea[1300];
  char *aux;
  int i, edadInt;
  while(fgets(linea, 1024, archivo) != NULL){ //Se leen todas las lineas en orden
    paciente* p = (paciente*) malloc(sizeof(paciente));
    p->medicos = createList();
    for(i = 0 ; i < 7 ; i++){//Se realizan 7 ciclos para permitir que se realizen las suficientes operaciones(6 valores en el struct)
        aux = get_csv_field(linea, i); //aux se convierte en la linea de caracteres i-esima para rellenar el valor correspondiente.
        if(i == 0){
        strcpy(p->nombre, aux);
        }
        if(i == 1){
        strcpy(p->apellido, aux);
        }
        if(i == 2){ 
        edadInt= atoi(aux);
        p->edad=edadInt;
        }
        if(i == 3){
        strcpy(p->telefono, aux);
        }
        if(i== 4){
        strcpy(p->direccion, aux);
        }
        if(i == 5){
        strcpy(p->numeroSocial, aux);
        Registrar(p, l);
        } 
        if(i == 6){
        asignarMedico(l, p->nombre, p->apellido, aux );
        }
      }
    }
  fclose(archivo);
}

void importarArchivos(){
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