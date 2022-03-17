#include "lista.h"

void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node));
    l->sentinel->next = l->sentinel;
    l->sentinel->prev = l->sentinel;
}

void wreckList (listaEnc *l) {
    while (!emptyList(l))
        removeStartList(l);
    free(l->sentinel);
    l->sentinel = NULL;
    l->qty = 0;
}

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    struct node* oldFirst = l->sentinel->next;
    newNode->data = num;
    newNode->next = oldFirst;
    newNode->prev = l->sentinel;
    oldFirst->prev = newNode;
    oldFirst = newNode;
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    struct node* oldLast = l->sentinel->prev;
    newNode->data = num;
    newNode->next = l->sentinel;
    newNode->prev = oldLast;
    oldLast->next = newNode;
    oldLast = newNode;
}
