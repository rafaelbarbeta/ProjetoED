#include "listapura.h"
#include <stdlib.h>

void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node)); //constrói o no sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para sí mesmo no next e prev
    l->sentinel->prev = l->sentinel;
}

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num; 
    newNode->next = l->sentinel->next; //o próximo depois do novo no é o antigo next da sentinela
    newNode->prev = l->sentinel; //a anterior é a propria sentinela
    l->sentinel->next->prev = newNode; //o prev do antigo primeiro (ou a sentinela) recebe o endereço do novo node
    l->sentinel->next = newNode; //o next da sentinela aponta para o início da lista, no caso, o novo node
    l->qty++;
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    newNode->next = l->sentinel; //o próximo depois do novo é a própria sentinela
    newNode->prev = l->sentinel->prev; //o anterior antes do novo é o antigo prev da sentinela
    l->sentinel->prev->next = newNode; //caso não seja o único, o next do antigo último apontara para o novo primeiro
    l->sentinel->prev = newNode; //o prev da sentinela aponta para o último da lista, no caso, o novo node
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
    struct node *lastNode = l->sentinel->prev; //cria uma variável estática que recebe sentinel prev
    if(!emptyList(l)){ //verifica se a lista não está vazia
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
    struct node *newNode = l->sentinel->prev; //cria uma variável estática que recebe sentinel prev
    if(newNode==l->sentinel){ //se essa variável for igual ao sentinel significa que a lista está vazia
        return 1; //está vazia
    }
    else{ //caso contrário significa que a lista nâo está vazia
        return 0;
    }
}

void wreckList (listaEnc *l) { 
    while (!emptyList(l)) //destrói elemento a elemento. Complexidade O(n)
        removeStartList(l);
    free(l->sentinel); //libera a sentinela
    l->sentinel = NULL; //faz o ponteiro apontar para o NULL (evita dangling pointer)
    l->qty = 0;
}