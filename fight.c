#include <stdio.h>
#include <stdbool.h>
#include "estructuras.h"
#include <windows.h>
#include "fight.h"
#include "gotoxy.h"
#define Barra "------------"
#define BARRA "-------------------------------------------------------"

void winScreen(){
}

int seleccionador(int opciones){
  int *option = 0;
  GetAllKeys();
  
  gotoxy(0,3);
  printf("     Atacar\n");
  printf("     mostrarInventario\n");
  printf("     cubrirse\n");
  printf("     burlarse\n");

  while(true){
    limpiarFlecha(0, 3, opciones);
    //formatearOpcion(option, opciones);
    ubicarFlecha(0, 3, *option);
    if(cambiarOpcion(option, opciones)) break;
  }
  return *option;
}

int seleccionadorInv(jugador *player){
  int *option = 0;
  int opciones = player->size;
  GetAllKeys();
  
  for(int i = 0; i < opciones ; i++){
    gotoxy(0,3+i*3);printf (" y el merluso callambim bombim     %s", player->inventario[i].item);
  }

  while(true){
    limpiarFlecha(0, 3, opciones);
    //formatearOpcion(&option, opciones);
    ubicarFlecha(0, 3, *option);
    if(cambiarOpcion(option, opciones)) break;
  }
  return *option;
}

void atacar(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 2){
        float damage = (player->stats.fuerza)/2;
        enemy->stats.salud -= damage;
        printf("El enemigo se ha cubierto, solo le has hecho %.f de dano\n", damage);
        return;
    }
    else{
        int damage = player->stats.fuerza;
        enemy->stats.salud -= damage;
        printf("Le has hecho %u de dano al enemigo\n", damage);
        return;
    }
    if (accionEnemy == 0){
        int damage = enemy->stats.fuerza;
        player->stats.salud -= damage;
        printf("El enemigo te ha quitado %u de vida\n", damage);
    }
    if (accionEnemy == 1){
        printf("El enemigo solo te observa...\n");
        return;
    }
    if (accionEnemy == 3){
        printf("El enemigo dice que ni le dolio...\n");
        //aca se puede hacer un sistema de respuestas pseudo-aleatorio
        return;
    }
}

void mostrarInventario(jugador *player){
    int seleccion = seleccionadorInv(player);
    if (seleccion == 1){
        
    }
}

void cubrirse(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 1) printf("Te cubres... y el enemigo no actua!\n"); return;
    if (accionEnemy == 2) printf("Te cubres... y el enemigo tambien!\n"); return;
    if (accionEnemy == 3) printf("Te cubres... y el enemigo se burla de ti!\n"); return;
    if (accionEnemy == 0){
        float damage = (enemy->stats.fuerza)/2;
        player->stats.salud -= damage;
        printf("Te cubres... y el enemigo solo te ha quitado %.f de vida!\n", damage);
        return;
    }
}
void burlarse(){
    int burla = rand() % 10;

    if (burla == 0) printf("");
    if (burla == 1) printf("");
    if (burla == 2) printf("");
    if (burla == 3) printf("");
    if (burla == 4) printf("");
    if (burla == 5) printf("");
    if (burla == 6) printf("");
    if (burla == 7) printf("");
    if (burla == 8) printf("");
    if (burla == 9) printf("");
    
}

void fight(jugador *player, enemigo *enemy){
    while (enemy->stats.salud > 0 || player->stats.salud > 0){
        int accionEnemy = rand() % 4;

        int seleccion = seleccionador(4);
        if (seleccion == 1) atacar(player, enemy, accionEnemy);{
            if (player->stats.salud <= 0) /*game_Over();*/ return;
            if (enemy->stats.salud <= 0) winScreen(); return;
        }
        if (seleccion == 2) mostrarInventario(player);
        if (seleccion == 3) cubrirse(player, enemy, accionEnemy);
        if (seleccion == 4) burlarse();
        
        puts(Barra);
        printf("| Vida Jugador: %u |\n", player->stats.salud);
        puts(Barra);

        puts("\n" Barra);
        printf("| Vida Enemigo: %u |\n", enemy->stats.salud);
        puts(Barra);
    }
}