#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "estructuras.c"
#include "gotoxy.h"
#define BARRA "-------------------------------------------------------"

//funciones del Nemeyas, no tocar
void limpiarFlecha(int x, int y, int cantOpciones){
    for(int i = 0; i < cantOpciones; i++){
        gotoxy(x, y + i*3); 
        printf("   ");
    }
}



void formatearOpcion(int* opcion, int cantOpciones){
    *opcion = *opcion % 3;
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
    gotoxy(10, 10); printf("Ejemplo de subrutina que se puede");
    gotoxy(10, 11); printf("realizar, sin salir del propio menu");
    gotoxy(10, 12); system("pause");
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

void inicio(){
  system("cls");
  int respuesta;
  printf("24/05/2023  (DIA DEL COMPLETO)\n\n");
  printf("Eres un estudiante de la 'prestigiosa' PUCV, hoy estas esperando la renovacion del 'CAE'\n");
  printf("sin embargo, al entrar al sistema, te das cuenta de que no renovaste dentro del plazo.\n");
  printf("En tu desesperacion por no saber que hacer y que tus padres te van a matar, acudes a la 'Casa Central',\n");
  printf("una vez en el lugar, te recibe una amable senorita, la cual te recuerda todos los meses que debes,\n\n");
  printf("Hola, ¿en que puedo ayudarte?\n");
  printf("1.Hola, tuve un problema con la renovacion y no se como pagar(1)\n");
  printf("2.Wena po, oe devuelvan la jabonera al ibc piso 2.(2)\n");

  scanf("%hu", &respuesta);
  while(respuesta > 2 || respuesta < 1){
    printf("Debe ingresar un numero valido (1;2)\n");
    scanf("%hu", &respuesta);
  }
  if(respuesta==1){
    printf("Asi veo, en el sistema figura que usted debe un total de 3 meses, lo siento pero debo llamar a los guardias.\n\n");
    printf("Al no presentar ninguna solucion de tu parte para pagar, la amable senorita llama a los guardias de seguridad,\n");
    printf("los cuales te meten el wuate mas exotico que tu cabeza haya podido sentir alguna vez, por lo que pierdes la conciencia\n");
    printf("Al despertar, estas en una prision, te encuentras muy desconcertado, no sabes que dia es ni que hora es,\n");
    printf("despues de unos instantes te das cuenta que estas sentado frente a un hombre de simpatico cabello largo, de unos 30-38 años\n");

  }
  else if (respuesta == 2){
    printf("Eso lo tiene que ver tu jefe de carrera");
    return;
  }
  while(respuesta > 2 || respuesta < 1){
    printf("Debe ingresar un numero valido (1;2)\n");
    scanf("%hu", &respuesta);
  }
    
  printf("\n\n");
}

void seleccionador(Grafo *g){
  for(char a=firstList(); a==NULL;nextList()){
    if(strcmp(a,'pause')){
      system('pause')
    }
    if(strcmp(a,"fight")){
      pelea()
    }
    if(strcmp(a,'choice'))
    else{
      printf(a)
    }
  }
}

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

int main(void) {
  int seleccion=0;
  Grafo* grafo = createGrafo();
  printf("Escriba el nombre del archivo\n");
      FILE *archivo = fopen('sucesos.csv',"rt");
      if (archivo == NULL) {
        printf("* Error al abrir el archivo.\n");
      } else{
         importar(grafo, archivo);
      }
  GetAllKeys();
  ocultarCursor();
  //unsigned short num;
  mostrarMenu();
  /*scanf("%hu", &num);
  while(num > 2 || num < 0){
    printf("Debe ingresar un numero valido (0; 1; 2)\n");
    scanf("%hu", &num);
  }*/
  Node *nodoActual= firstList(grafo->nodos);
 /* 
  while(true){
    if (num == 0) {// Si se ingrea 0 se termina el programa
      printf("\n");
      puts(BARRA);
      printf("                   Fin Del Programa\n");
      puts(BARRA);
      return 0;
    }

    if (num == 1) {
      inicio();
      system("cls");
      if(selecion==1)
        ruta1();
      if(seleccion==2){
        ruta2();
      }
      if(seleccion==3){
        ruta3();
      }
      return 1;
    }
    if (num == 2) {
      return 1;
    }
  }*/
  return 0;
}