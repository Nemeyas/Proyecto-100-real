//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 0218 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h

typedef struct HashMap HashMap;
typedef struct Node Node;

typedef struct Pair {
     void * key;
     void * value;
} Pair;

struct HashMap {
  Pair ** buckets;
  long size; //cantidad de datos/pairs en la tabla
  long capacity; //capacidad de la tabla
  long current; //indice del ultimo dato accedido
};

HashMap * createMap(long capacity);

void insertMap(HashMap * map, char * key, void * value);

void eraseMap(HashMap * map, char * key);

Node * searchMap(HashMap * map, char * key);

Node * firstMap(HashMap * map);

Node * nextMap(HashMap * map);

void enlarge(HashMap * map);

#endif /* HashMap_h */