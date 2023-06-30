#ifndef fight_h
#define fight_h

typedef struct jugador jugador;
typedef struct enemigo enemigo;
typedef struct inve inve;

void winScreen();
int seleccionador(int opciones);
int seleccionadorInv(jugador *player);
void atacar(jugador *player, jugador *enemy, int accionEnemy);
void mostrarInventario(jugador *player);
void cubrirse(jugador *player, jugador *enemy, int accionEnemy);
void burlarse();
void fight(jugador *player, jugador *enemy);

#endif /* fight_h */