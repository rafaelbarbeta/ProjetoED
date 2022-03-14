#ifndef LISTA_H

#define LISTA_H
#include "lista.c"

typedef int type;
typedef struct {
    struct node *sentinela;
    unsigned int quantidade;
} listaEnc;

struct node {
    struct node *next, *prev;
    type data;
};

void inicializa (listaEnc *pont);
int vazia (listaEnc *pont);
void inserirInicio (listaEnc *pont, type num);
void inserirFinal (listaEnc *pont, type num);
void removeInicio (listaEnc *pont);
void removeFinal (listaEnc *pont);
unsigned int tamanho (listaEnc *pont);
type vizualizarInicio (listaEnc *pont);
type vizualizarFinal (listaEnc *pont);
void destroi (listaEnc *pont);

#endif 