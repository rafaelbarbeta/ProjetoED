#ifndef DEQUE_H

#define DEQUE_H
#include "deque.c"

typedef int type;
typedef struct {
    unsigned int head;
    unsigned int tail;
    type *vect;
} deque;

void startDeque (deque *d, unsigned int size); //inicia
int emptyDeque (deque *d); //vazio
int fullDeque (deque *d); //cheio
void nextDeque (deque *d, unsigned int *index); //proximo
int addStartDeque (deque *d, type num); //inseri (inicio)
int addEndDeque (deque *d, type num); //inseri (final)
int removeStartDeque (deque *d); //remove (inicio)
int removeEndDeque (deque *d); //remove (final)
type viewStartDeque (deque *d); //visualizar (inicio)
type viewEndDeque (deque *d);  //visualizar (final)
void wreckDeque (deque *d); //destroi

#endif
