#define Barra "------------"

void atacar(jugador *player, enemy *enemy, int accionEnemy){
    if (accionEnemy == 3){
        float damage = (player->stats->fuerza)/2;
        enemy->stats->vida -= damage;
        printf("El enemigo se ha cubierto, solo le has hecho %.f de daño\n", damage);
        return;
    }
    else{
        int damage = player->stats->fuerza;
        enemy->stats->vida -= damage;
        printf("Le has hecho %u de daño al enemigo\n", damage);
        return;
    }
    if (accionEnemy == 1){
        int damage = enemy->stats->fuerza;
        player->stats->vida -= damage;
        printf("El enemigo te ha hecho %u de daño\n", damage);
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

void mostrarInventario(Inv *inventario){
    int seleccion = seleccionadorInv(*inventario->size, *inventario);
    if (seleccion == 1){
    }
}

void cubrirse(jugador *player, enemy *enemy, int accionEnemy){
    if (accionEnemy == 2) printf("Te cubres... y el enemigo no actua!\n"); return;
    if (accionEnemy == 3) printf("Te cubres... y el enemigo también!\n"); return;
    if (accionEnemy == 4) printf("Te cubres... y el enemigo se burla de ti!\n"); return;
    if (accionEnemy == 1){
        float damage = (enemy->stats->fuerza)/2;
        player->stats->vida -= damage;
        printf("Te cubres... y el enemigo solo te ha quitado %.f de daño!\n", damage);
        return;
    }
}
void burlarse(){
    int burla = random(1,10);
    
}
void fight(enemy *enemy, jugador *player){
    while (enemy->stats->vida > 0 || player->stats->vida > 0){
        int accionEnemy = random(1,4);

        int seleccion = seleccionador(4);
        if (seleccion == 1) atacar(player, enemy, accionEnemy);{
            if (player->stats->vida <= 0) gameOver(); return;
            if (enemy->stats->vida <= 0) winScreen(); return;
        }
        if (seleccion == 2) mostrarInventario(player->inventario);
        if (seleccion == 3) cubrirse(player, enemy, accionEnemy);
        if (seleccion == 4) burlarse();
        
        puts(Barra);
        puts("| Vida Jugador: %u |", player->stats->vida);
        puts(Barra);

        puts("\n" Barra);
        puts("| Vida Enemigo: %u |", enemy->stats->vida);
        puts(Barra);
    }
}

