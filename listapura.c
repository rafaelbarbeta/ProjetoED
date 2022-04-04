#include "listapura.h"
#include <stdlib.h>

/* funções da lista sem iterador*/
void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node)); //constroi o no sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para si mesmo no next e prev
    l->sentinel->prev = l->sentinel;
}

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num; 
    newNode->next = l->sentinel->next; //o proximo depois do novo no eh o antigo next da sentinela
    newNode->prev = l->sentinel; //a anterior eh a propria sentinela
    l->sentinel->next->prev = newNode; //o prev do antigo primeiro (ou a sentinela) recebe o endereco do novo node
    l->sentinel->next = newNode; //o next da sentinela aponta para o inicio da lista, no caso, o novo node
    l->qty++;
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    newNode->next = l->sentinel; //o proximo depois do novo eh a propria sentinela
    newNode->prev = l->sentinel->prev; //o anterior antes do novo eh o antigo prev da sentinela
    l->sentinel->prev->next = newNode; //caso nao seja o unico, o next do antigo ultimo apontara para o novo primeiro
    l->sentinel->prev = newNode; //o prev da sentinela aponta para o ultimo da lista, no caso, o novo node
    l->qty++;
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


void removeEndList (listaEnc *l){
    struct node *lastNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(!emptyList(l)){ //verifica se a lista nao esta vazia
        lastNode->next->prev = lastNode->prev;
        lastNode->prev->next = lastNode->next;
        free(lastNode); //desaloca
        l->qty--;
    }
}

void removeStartList (listaEnc *l) {
    struct node *firstNode = l->sentinel->next;
    if (!emptyList(l)) {
        firstNode->next->prev = firstNode->prev;
        firstNode->prev->next = firstNode->next;
        free(firstNode);
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

void wreckList (listaEnc *l) {
    while (!emptyList(l))
        removeStartList(l);
    free(l->sentinel);
    l->sentinel = NULL;
    l->qty = 0;
}