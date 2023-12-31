#ifndef fight_h
#define fight_h

typedef struct jugador jugador;
typedef struct enemigo enemigo;
typedef struct inve inve;

void seleccionador(int accionEnemy, jugador *player, enemigo *enemy, int  contPiedra, int contPie, int contZapatilla, int contFoto, int *contInv);
void seleccionadorInv(jugador *player, enemigo *enemy, int accionEnemy,int piedra,int pie,int zapatilla,int abuela);
void atacar(jugador *player, enemigo *enemy, int accionEnemy);
void cubrirse(jugador *player, enemigo *enemy, int accionEnemy);
void burlarse(enemigo *enemy, jugador *player, int accionEnemy);
void fight(jugador *player, enemigo *enemy);

#endif /* fight_h */