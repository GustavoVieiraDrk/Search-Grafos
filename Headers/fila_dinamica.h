#ifndef FILA_DINAMICA_H_INCLUDED
#define FILA_DINAMICA_H_INCLUDED

struct info{
    int valor;
};

typedef struct info Info;
typedef struct elemento tpElemento;
typedef struct elemento* apElemento;
typedef struct fila* Fila;

Fila create_queue();
int empty_queue(Fila f);

void insert_queue(Fila f, Info i);
Info remove_queue(Fila f);

void print_queue(Fila f);
void free_queue(Fila f);

#endif
