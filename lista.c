#include "lista.h"
#include <stdlib.h>

void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node));
    l->sentinel->next = l->sentinel;
    l->sentinel->prev = l->sentinel;
}

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    newNode->next = l->sentinel->next;
    newNode->prev = l->sentinel;
    if (l->sentinel->next == l->sentinel)
        l->sentinel->prev = newNode;
    else
        l->sentinel->next->prev = newNode;
    l->sentinel->next = newNode;
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    newNode->next = l->sentinel;
    newNode->prev = l->sentinel->prev;
    if (l->sentinel->prev == l->sentinel)
        l->sentinel->next = newNode;
    else
        l->sentinel->prev->next = newNode;
    l->sentinel->prev = newNode;
}

type viewStartList (listaEnc *l) {
    return (l->sentinel->next->data); //retorna data do posterior ao sentinela
}

type viewEndList (listaEnc *l) {
    return (l->sentinel->prev->data); //retorna data do anterior ao sentinela 
}

unsigned int sizeList (listaEnc *l) {
    return (l->qty); //retorna qtd nodes
}

void wreckList (listaEnc *l) {
    while (!emptyList(l))
        removeStartList(l);
    free(l->sentinel);
    l->sentinel = NULL;
    l->qty = 0;
}