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

/*void ruta1(){
  if()
      printf("¡Hola!, soy Ignacio Araya, el dueno de la prision.\n");
      printf("¿Asi que tu eres el que no pago la mensualidad?\n");
      printf("Bueno, ocurre mucho ultimamente, ¿cual es tu nombre?\n\n");
      char nombre[31];
      printf("<(Ingrese su nombre de jugador)>\n");
      scanf(" %[^\n]", nombre);
      registrar(nombre);  
      printf("Bueno, %s, espero tengas una buena estadia en tus 3 anios de condena, tu celda es la numero 11, un guardia te llevara para alla\n", nombre);
      printf("Ya llevas 2 dias en esta prision, lo unico que esta a tu vista son las celdas 13 y 5, ademas de sus extranos residentes, te sientes aburrido de estar ahi...\n");
      printf("<(¿Quieres escapar de la prision? (1))>\n <(¿Quieres cumplir tu condena? (2))>\n");
      unsigned short es;
      scanf("%hu",&es);
      while(es > 2 || es < 1){
        printf("Debe ingresar un numero valido (1; 2)\n");
        scanf("%hu", &es);
      }
      if(es == 2){
        printf("Despues de 3 largos anios, se te ha dejado en libertad, el mismisimo dueno de la prision (Ignacio) te ha acompanado hasta la puerta,\n");
        printf("en donde te desea suerte y que mires para ambos lados de la calle al cruzar. Al salir te das cuenta de que estabas ubicado en Petorca, con razon\n");
        printf("Solo los dejaban banarse 1 vez a la semana. Empiezas a caminar en cualquier direccion en busca de algun buen samaritano que te lleve a Valparaiso,\n");
        printf("Llegas al paradero mas cercano y comienzas a esperar...\n ... \n ... \n llega finalmente aparece una micro y te subes sin pensarlo. \n Sin embargo te das cuenta ya a mitad de camino de que no tienes dinero para el pasaje, maldices tu suerte comienzas a pensar \n");
        printf("<(Que hago?!)> \n 1.matarme \n 2. Esperar a ver que pasa.\n");
        return 1;
      }
}*/

int main(void) {
  int seleccion=0;
  Grafo* grafo = createGrafo();
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
  printf(" Hola");
  return 0;
}