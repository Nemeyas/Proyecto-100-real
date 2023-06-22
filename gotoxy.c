#include <stdio.h>
#include <windows.h> //Libreria necesaria para manipular la consola de salida
#include <stdbool.h>
#include <stdlib.h>
#include "gotoxy.h"


/*La funcion recibe los parametros x, y
* y situa el cursor en esa posiccion */
void gotoxy(int x, int y){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    //Eje invertido, con y = 0 en la primera linea, y > 0 desde la segunda linea en adelante
    pos.Y = y; 
    SetConsoleCursorPosition(consola, pos);
}

/*Funcion que oculta el cursor. Si tiene dudas con esta existen
* variados sitios en internet de donde obtener documentacion*/
void ocultarCursor(){
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursInfo;
    cursInfo.dwSize = 2;
    cursInfo.bVisible = FALSE;
    SetConsoleCursorInfo( consola, &cursInfo);
}

//*Funcion propuesta*
//Obtiene todas las teclas que se utilizan en el juego
void GetAllKeys(){
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState(VK_RETURN);
}


/*
Colores 
0 = Negro
1= Azul
2= Verde
3= Aguamarina
4= Rojo
5= Purpura
6= Amarillo
7= Blanco
8= Gris
9= Azul Claro
A= Verde Claro
B= Aguamarina Claro
C= Rojo Claro
D= Purpura Claro
E= Amarillo Claro
F= Blanco Brillante
*/