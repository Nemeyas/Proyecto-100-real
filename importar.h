#ifndef importar_h
#define importar_h

void importarDatos(Grafo *g, char* archivoName);
void importarArchivos(Grafo *g, HashMap *enemies);
void importarImagen(Grafo *g, char* archivoName);
void importarEnemigos(HashMap *enemies, char *archivoName);
void importarSave(Grafo *g, Node *nodoActual, jugador *player);
#endif