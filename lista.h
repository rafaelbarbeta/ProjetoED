#ifndef LISTA_H

#define LISTA_H
#include "lista.c"

typedef int type;
typedef struct {
    struct node *sentinel;
    unsigned int qty;
} listaEnc;

struct node {
    struct node *next, *prev;
    type data;
};

void startList (listaEnc *pont); //inicia
int emptyList (listaEnc *pont); //vazio
void addStartList (listaEnc *pont, type num); //inseri (inicio)
void addEndList (listaEnc *pont, type num); //inseri (final)
void removeStartList (listaEnc *pont); //remove (inicio)
void removeEndList (listaEnc *pont); //remove (final)
unsigned int sizeList (listaEnc *pont); //tamanho
type viewStartList (listaEnc *pont); //visualizar (inicio)
type viewEndList (listaEnc *pont); //visualizar (final)
void wreckList (listaEnc *pont); //destroi

#endif 