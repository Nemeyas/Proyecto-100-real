#ifndef fight_h
#define fight_h

typedef struct jugador jugador;
typedef struct enemigo enemigo;
typedef struct inve inve;

void seleccionador(int opciones, jugador *player, enemigo *enemy);
void seleccionadorInv(jugador *player, enemigo *enemy,int *piedra,int *pie,int *zapatilla,int *abuela);
void atacar(jugador *player, enemigo *enemy, int accionEnemy);
void mostrarInventario(jugador *player);
void cubrirse(jugador *player, enemigo *enemy, int accionEnemy);
void burlarse(enemigo *enemy);
void fight(jugador *player, enemigo *enemy);

#endif /* fight_h */