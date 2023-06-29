#ifndef importar_h
#define importar_h

void importarDatos(Grafo *g, char* archivoName);
void importarArchivos(Grafo *g, HashMap *enemies, jugador *player, Node *nodoActual);
void importarImagen(Grafo *g, char* archivoName);
void importarEnemigos(HashMap *enemies, char *archivoName);
void importarSave(Grafo *g, Node *nodoActual, jugador *player);
void subrutina(Grafo *g, Node *nodoActual, jugador *player);
void save(Grafo *g, Node* nodo, jugador *player);
void guardarPartida(Grafo *g, Node *n, jugador *player);
int verificarArchivo(const char* nombreArchivo);
#endif