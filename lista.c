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

void removeEndList (listaEnc *l){
    struct node *newNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(newNode != l->sentinel){ //verifica se a lista nao esta vazia, pode ser feito chamando a funcao para verificar, nesse caso aprenas comparei o valor do new world com a sentinel dessa forma nao precisa chamar outra funcao
        newNode->next->prev = newNode->prev;
        newNode->prev->next = newNode->next;
        free(newNode); //desaloca
        l->qty--;
    }
}

int emptyList (listaEnc *l){
    struct node *newNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(newNode==l->sentinel){ //se essa variavel for igual ao sentinel significa que a lista esta vazia
        return 1; //esta vazia
    }
    else{ //caso contrario significa que a lista nao esta vazia
        return 0;
    }
}