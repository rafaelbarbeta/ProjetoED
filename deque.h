#ifndef DEQUE_H

#define DEQUE_H
#include "deque.c"

typedef int type;
typedef struct {
    unsigned int head;
    unsigned int tail;
    type *vet;
} deque;

void inicializa (deque *d, unsigned int tam);
int vazio (deque *d);
int cheio (deque *d);
void proximo (deque *d, unsigned int *index);
int adicionaInicio (deque *d, type num);
int adicionaFinal (deque *d, type num);
int removeInicio (deque *d);
int removeFinal (deque *d);
type visualizarInicio (deque *d);
type visualizarFinal (deque *d);
void destroi (deque *d);

#endif
