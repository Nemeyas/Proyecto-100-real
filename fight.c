#include <stdio.h>
#include <stdbool.h>
#include "estructuras.h"
#include <windows.h>
#include "fight.h"
#include "gotoxy.h"
#include "Imagen.h"
#define Barra "--------------------"
#define BARRA "-------------------------------------------------------"

void gameOver(){//Funcion que opera despues de que el jugador muera
    printf("HAS MUERTO!!)(!=)!=)==!!");
    system("pause");
}

void atacar(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 2){
        int damage = (player->stats.fuerza)/2;
        enemy->stats.salud -= damage;
        printf("El enemigo se ha cubierto, solo le has hecho quitado %u de vida\n", damage);
        system("pause");
        system("cls");
        return;
    }
    else{
        int damage = player->stats.fuerza;
        enemy->stats.salud -= damage;
        printf("Le has hecho %u de dano al enemigo\n", damage);
        system("pause");
        system("cls");
    }
    if (accionEnemy == 0){
        int damage = enemy->stats.fuerza;
        player->stats.salud -= damage;
        printf("El enemigo te ha quitado %u de vida\n", damage);
        system("pause");
        system("cls");
        return;
    }
    if (accionEnemy == 1){
        printf("El enemigo solo te observa...\n");
        system("pause");
        system("cls");
        return;
    }
    if (accionEnemy == 3){
        printf("El enemigo dice que ni le dolio...\n");
        system("pause");
        system("cls");
        return;
    }
}

void cubrirse(jugador *player, enemigo *enemy, int accionEnemy){
    if (accionEnemy == 1) {
        printf("Te cubres... y el enemigo no actua!\n");
        system("pause");
        return;
    }
    if (accionEnemy == 2){
        printf("Te cubres... y el enemigo tambien!\n");
        system("pause");
        return;
    }   
    if (accionEnemy == 3){
        printf("Te cubres... y el enemigo se burla de ti!\n");
        system("pause");
        return;
    }     
    if (accionEnemy == 0){
        int damage = (enemy->stats.fuerza)/2;
        player->stats.salud -= damage;
        printf("Te cubres... y el enemigo solo te ha quitado %.u de vida!\n", damage);
        system("pause");
        return;
    }
}

void burlarse(enemigo *enemy, jugador *player, int accionEnemy){
    int burla = rand() % 10;
    if (burla == 0) printf("Tu mama es guatona\n");
    if (burla == 1) printf("Gohan acercate...Esta a un toque\n");
    if (burla == 2) printf("chatarra tu abuela\n");
    if (burla == 3) printf("calmao que tengo que atacar en la guerra del clan\n");
    if (burla == 4) printf("*procede a baile de Fortnite*\n");
    if (burla == 5) printf("igual gracias\n");
    if (burla == 6) printf("tu mamita\n");
    if (burla == 7) printf("Se busca rival en la PUCV\n");
    if (burla == 8) printf("Mi primo chico dio mas pelea... contra el cancer\n");
    if (burla == 9){
        printf(" Tu: Loco que esta pasando, maniana mismo hago la denuncia en la PDI\n");
        printf(" Guardia: otra vez noooo, esa vez me dijo que tenia 18");
        system("pause");
        system("cls");
        printf("El enemigo huyo!\n");
        enemy->stats.salud = 0;
    }

    if (accionEnemy == 0){
        int damage = enemy->stats.fuerza;
        player->stats.salud -= damage;
        printf("El %s se encabrono y te pego %u de danio\n",enemy->nombre, damage);
        system("pause");
        system("cls");
        return;
    }
    if (accionEnemy == 1){
        printf("El %s solo te observa... con odio\n",enemy->nombre);
        system("pause");
        system("cls");
        return;
    }
    if (accionEnemy == 2){
        printf("El %s se ha cubierto, pero el danio emocional no se quita\n",enemy->nombre);
        system("pause");
        system("cls");
        return;
    }
    if (accionEnemy == 3){
        printf("%s se bajoneo entero...\n", enemy->nombre);
        system("pause");
        system("cls");
        return;
    }
    
    system("pause");
}

void seleccionadorInv(jugador *player, enemigo *enemy, int accionEnemy,int piedra,int pie,int zapatilla,int abuela){   //aqui lo cambian a tipo int
    int option = 0;
    int opciones = player->size;
    GetAllKeys();
    while(true){
        system("cls");
        mostrarImagen("guardia");
        gotoxy(6,27);printf("Selecciona el item que quieras usar");
        gotoxy(6,29);printf("piedra");
        gotoxy(6,32);printf("Pie de Limon");
        gotoxy(6,35);printf("zapatilla desgastada");
        gotoxy(6,38);printf("Foto de tu abuela");

        while(true){
            limpiarFlecha(0, 29, 4);
            ubicarFlecha(0, 29, option);
            if(cambiarOpcion(&option, 4)) break;
            mostrarImagen("guardia");
        }

        switch(option)
        {
        case 0:
            if(piedra==0){
                printf("Te quedaste sin piedras");
                return;
            }
            enemy->stats.salud-=10;
            piedra-=1;
        case 1:
            if(pie==0){
                printf("Te comiste todo el Pie");
                return;
            }
            player->stats.salud+=10;
            pie-=1;
        case 2:
            if(zapatilla==0){
                printf("Perdiste todas tus tillas");
                return;
            }
            enemy->stats.fuerza-=2;
            zapatilla-=1;
        case 3:
            if(abuela==0){
                printf("La foto de tu abuela ya no te da inspiracion");
                return;
            }
            player->stats.fuerza+=2;
            abuela-=1;
        }
        if (accionEnemy == 0 || accionEnemy == 5){
            int damage = enemy->stats.fuerza;
            player->stats.salud -= damage;
            printf("El enemigo te ha quitado %u de vida\n", damage);
            system("pause");
            system("cls");
            return;
        }
        if (accionEnemy == 1 || accionEnemy ==2){
            printf("El enemigo solo te observa...\n");
            system("pause");
            system("cls");
            return;
        }
        if (accionEnemy == 3){
            printf("El enemigo dice que ni le dolio...\n");
            system("pause");
            system("cls");
            return;
        }
    }
}

void seleccionador(int accionEnemy, jugador *player, enemigo *enemy, int  contPiedra, int contPie, int contZapatilla, int contFoto, int *contInv){
    int seleccion = 0;
    GetAllKeys();
    while(true){

        mostrarImagen("guardia");
        system("cls");
        mostrarImagen("guardia");
        gotoxy(6,32);printf("     Atacar\n");
        gotoxy(6,35);printf("     mostrarInventario\n");
        gotoxy(6,38);printf("     cubrirse\n");
        gotoxy(6,41);printf("     burlarse\n");

        gotoxy(6,27);puts(Barra);
        gotoxy(6,28);printf("| Vida %s: %d \n", player->nombre, player->stats.salud);
        gotoxy(6,29);puts(Barra);

        gotoxy(137,27);puts(Barra);
        gotoxy(137,28);printf(" Vida %s: %d |\n", enemy->nombre, enemy->stats.salud);
        gotoxy(137,29);puts(Barra);

        while(true){
            limpiarFlecha(0, 32, 4);
            ubicarFlecha(0, 32, seleccion);
            if(cambiarOpcion(&seleccion,4)) break;
            mostrarImagen("guardia");
        }

        if (seleccion == 0){
            atacar(player, enemy, accionEnemy);
            return;
        }
        if (seleccion == 1){
            
            if(*contInv == 3){
                printf("no puedes acceder a tu inventario en este turno");
                system("pause");
                return;
            }
            seleccionadorInv(player,enemy,accionEnemy,contPiedra,contPie,contZapatilla,contFoto);
            *contInv+=1;
            return;
        } 
        if (seleccion == 2){
            cubrirse(player, enemy, accionEnemy);
            return;
        } 
        if (seleccion == 3){
            burlarse(enemy, player, accionEnemy);
            return;
        }
  }
}

void fight(jugador *player, enemigo *enemy){
    int contPiedra=2;
    int contPie=1;
    int contZapatilla=4;
    int contFoto=4;
    int contInv=0;
    while (enemy->stats.salud > 0 || player->stats.salud > 0){
        int accionEnemy = rand() % 6;

        seleccionador(accionEnemy, player, enemy, contPiedra, contPie, contZapatilla, contFoto, &contInv);
        if (player->stats.salud <= 0){
            gameOver();
            creditos();
            return;
        }
        if (enemy->stats.salud <= 0){
            system("cls");
            return;
        } 
    }
}
