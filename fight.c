/*

#include <stdio.h>
#include "estructuras.h"
#include <windows.h>
#define Barra "------------"
#define BARRA "-------------------------------------------------------"

void winScreen(){
    cls();
}

int seleccionador(int opciones){
  int option = 0;
  GetAllKeys();
  
  gotoxy(0,3);
  printf("     Atacar\n");
  printf("     mostrarInventario\n");
  printf("     cubrirse\n");
  printf("     burlarse\n");

  while(true){
    limpiarFlecha(0, 3, opciones);
    formatearOpcion(&option, opciones);
    ubicarFlecha(0, 3, option);
    if(cambiarOpcion(&option)) break;
  }
  return option;
}

int seleccionadorInv(int opciones, inve *inventario){
  int option = 0;
  GetAllKeys();
  
  gotoxy(0,3);
  for(int i=0; i<opciones ;i++){
    printf (" y el merluso callambim bombim     %s", inventario[i].item);
  }

  while(true){
    limpiarFlecha(0, 3, opciones);
    formatearOpcion(&option, opciones);
    ubicarFlecha(0, 3, option);
    if(cambiarOpcion(&option)) break;
  }
  return option;
}

void atacar(jugador *player, jugador *enemy, int accionEnemy){
    if (accionEnemy == 3){
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
    if (accionEnemy == 1){
        int damage = enemy->stats.fuerza;
        player->stats.salud -= damage;
        printf("El enemigo te ha quitado %u de vida\n", damage);
    }
    if (accionEnemy == 2){
        printf("El enemigo solo te observa...\n");
        return;
    }
    if (accionEnemy == 4){
        printf("El enemigo dice que ni le dolio...\n");
        //aca se puede hacer un sistema de respuestas pseudo-aleatorio
        return;
    }
}

void mostrarInventario(inve *inventario){
    int seleccion = seleccionadorInv(inventario->size, &inventario);
    if (seleccion == 1){
        
    }
}

void cubrirse(jugador *player, jugador *enemy, int accionEnemy){
    if (accionEnemy == 2) printf("Te cubres... y el enemigo no actua!\n"); return;
    if (accionEnemy == 3) printf("Te cubres... y el enemigo tambien!\n"); return;
    if (accionEnemy == 4) printf("Te cubres... y el enemigo se burla de ti!\n"); return;
    if (accionEnemy == 1){
        float damage = (enemy->stats.fuerza)/2;
        player->stats.salud -= damage;
        printf("Te cubres... y el enemigo solo te ha quitado %.f de vida!\n", damage);
        return;
    }
}
void burlarse(){
    int burla = random(1,10);
    
}

void fight(jugador *enemy, jugador *player){
    while (enemy->stats.salud > 0 || player->stats.salud > 0){
        int accionEnemy = random(1,4);

        int seleccion = seleccionador(4);
        if (seleccion == 1) atacar(player, enemy, accionEnemy);{
            if (player->stats.salud <= 0) game_Over(); return;
            if (enemy->stats.salud <= 0) winScreen(); return;
        }
        if (seleccion == 2) mostrarInventario(player->inventario);
        if (seleccion == 3) cubrirse(player, enemy, accionEnemy);
        if (seleccion == 4) burlarse();
        
        puts(Barra);
        printf("| Vida Jugador: %u |\n", player->stats.salud);
        puts(Barra);

        puts("\n" Barra);
        printf("| Vida Enemigo: %u |\n", enemy->stats.salud);
        puts(Barra);
    }
}*/