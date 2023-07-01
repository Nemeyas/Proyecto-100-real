#ifndef fight_h
#define fight_h

typedef struct jugador jugador;
typedef struct enemigo enemigo;
typedef struct inve inve;

void winScreen();
int seleccionador(int opciones);
int seleccionadorInv(jugador *player);
void atacar(jugador *player, enemigo *enemy, int accionEnemy);
void mostrarInventario(jugador *player);
void cubrirse(jugador *player, enemigo *enemy, int accionEnemy);
void burlarse();
void fight(jugador *player, enemigo *enemy);

#endif /* fight_h */