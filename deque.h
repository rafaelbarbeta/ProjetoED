#ifndef DEQUE_H

#define DEQUE_H
#include "deque.c"
#include <stdlib.h>

typedef int type;
typedef struct {
    unsigned int head;
    unsigned int tail;
    type *vet;
} deque;

void inicializa (type *deque, unsigned int tam);
int vazio (type *deque);
int cheio (type *deque);
void proximo (type *deque, unsigned int *index);
int adicionaInicio (type *deque, type num);
int adicionaFinal (type *deque, type num);
int removeInicio (type *deque);
int removeFinal (type *deque);
type visualizarInicio (type *deque);
type visualizarFinal (type *deque);
void destroi (type *deque);

#endif
