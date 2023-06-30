#ifndef Gotoxy_h
#define Gotoxy_h

void game();

void gotoxy(int x, int y);

void GetAllKeys();

void ocultarCursor();

void limpiarFlecha(int x, int y, int cantOpciones);

void ubicarFlecha(int x, int y, int opcion);

bool cambiarOpcion(int * opcion, int cantOpciones);

//int formatearOpcion(option, opciones);

#endif /* Gotoxy_h */