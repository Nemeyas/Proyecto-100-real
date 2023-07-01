#include <stdio.h>
#include <stdbool.h>
#include "estructuras.h"
#include <windows.h>
#include "fight.h"
#include "gotoxy.h"
#define Barra "------------"
#define BARRA "-------------------------------------------------------"

void gameOver(){
    printf("HAS MUERTO!!)(!=)!=)==!!");
    system("pause");
    abort();
}

void atacar(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 2){
        int damage = (player->stats.fuerza)/2;
        enemy->stats.salud -= damage;
        printf("El enemigo se ha cubierto, solo le has hecho quitado %u de vida\n", damage);
        system("pause");
        return;
    }
    else{
        int damage = player->stats.fuerza;
        enemy->stats.salud -= damage;
        printf("Le has hecho %u de dano al enemigo\n", damage);
        system("pause");
        return;
    }
    if (accionEnemy == 0){
        int damage = enemy->stats.fuerza;
        player->stats.salud -= damage;
        printf("El enemigo te ha quitado %u de vida\n", damage);
        system("pause");
        return;
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

void cubrirse(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 1) printf("Te cubres... y el enemigo no actua!\n"); return;
    if (accionEnemy == 2) printf("Te cubres... y el enemigo tambien!\n"); return;
    if (accionEnemy == 3) printf("Te cubres... y el enemigo se burla de ti!\n"); return;
    if (accionEnemy == 0){
        int damage = (enemy->stats.fuerza)/2;
        player->stats.salud -= damage;
        printf("Te cubres... y el enemigo solo te ha quitado %.u de vida!\n", damage);
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

void seleccionadorInv(jugador *player, enemigo *enemy,int *piedra,int *pie,int *zapatilla,int *abuela){
    int option = 0;
    int opciones = player->size;
    GetAllKeys();
    while(true){
        gotoxy(6,27);printf("Selecciona el item que quieras usar");
        system("cls");
        gotoxy(6,29);printf("piedra");
        gotoxy(6,32);printf("Pie de Limon");
        gotoxy(6,35);printf("zapatilla desgastada");
        gotoxy(6,38);printf("Foto de tu abuela");

        while(true){
            limpiarFlecha(0, 29, opciones);
            ubicarFlecha(0, 29, option);
            if(cambiarOpcion(&option, opciones)) break;
        }
        switch (option)
        {
        case 0:
            if(piedra==0){
                printf("Te quedaste sin piedras");
                return;
            }
            enemy->stats.salud-=10;
            piedra--;
            return;
        case 1:
            if(pie==0){
                printf("Te comiste todo el Pie");
                return;
            }
            player->stats.salud+=5;
            pie--;
            return;
        case 2:
            if(zapatilla==0){
                printf("Perdiste todas tus tillas");
                return;
            }
            enemy->stats.fuerza-=1;
            zapatilla--;
            return;
        case 3:
            if(abuela==0){
                printf("La foto de tu abuela ya no te da inspiracion");
                return;
            }
            player->stats.fuerza+=1;
            abuela--;
            return;
    }
    }
}

void seleccionador(int accionEnemy, jugador *player, enemigo *enemy){
    int seleccion = 0;
    int contPiedra=2;
    int contPie=1;
    int contZapatilla=4;
    int contFoto=4;
    GetAllKeys();
    while(true){
        system("cls");
        gotoxy(6,29);printf("     Atacar\n");
        gotoxy(6,32);printf("     mostrarInventario\n");
        gotoxy(6,35);printf("     cubrirse\n");
        gotoxy(6,38);printf("     burlarse\n");

        gotoxy(6,0);puts(Barra);
        gotoxy(6,1);printf("| Vida Jugador: %u |\n", player->stats.salud);
        gotoxy(6,2);puts(Barra);

        gotoxy(137,0);puts("\n" Barra);
        gotoxy(137,1);printf("| Vida Enemigo: %u |\n", enemy->stats.salud);
        gotoxy(137,2);puts(Barra);

        while(true){
            limpiarFlecha(0, 29, 4);
            ubicarFlecha(0, 29, seleccion);
            if(cambiarOpcion(&seleccion,4)) break;
        }

        if (seleccion == 0){
            atacar(player, enemy, accionEnemy);
        }
        if (seleccion == 1){
            seleccionadorInv(player,enemy,&contPiedra,&contPie,&contZapatilla,&contFoto);
        } 
        if (seleccion == 2){
            
        } cubrirse(player, enemy, accionEnemy);
        if (seleccion == 3) burlarse();
  }
}

void fight(jugador *player, enemigo *enemy){
    while (enemy->stats.salud > 0 || player->stats.salud > 0){
        int accionEnemy = rand() % 4;
        seleccionador(accionEnemy, player, enemy);
        if (player->stats.salud <= 0) /*game_Over();*/ return;
        if (enemy->stats.salud <= 0) return;
    }
}