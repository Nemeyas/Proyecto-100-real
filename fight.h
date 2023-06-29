#ifndef fight_h
#define fight_h

typedef struct jugador jugador;
typedef struct enemigo enemigo;
typedef struct inve inve;

void winScreen();
int seleccionador(int opciones);
int seleccionadorInv(int opciones, inve *inventario);
void atacar(jugador *player, enemigo *enemy, int accionEnemy);
void mostrarInventario(inve *inventario);
void cubrirse(jugador *player, enemigo *enemy, int accionEnemy);
void burlarse();
void fight(enemigo *enemy, jugador *player);

#endif /* fight_h */