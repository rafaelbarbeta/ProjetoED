#include "lista.h"
#include <stdlib.h>

/* funções da lista sem iterador*/
void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node)); //constroi o node sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para si mesmo no next e prev
    l->sentinel->prev = l->sentinel;
}

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num; 
    newNode->next = l->sentinel->next; //o proximo depois do novo no eh o antigo next da sentinela
    newNode->prev = l->sentinel; //a anterior eh a propria sentinela
    if (l->sentinel->next == l->sentinel) 
        l->sentinel->prev = newNode; //caso seja o unico elemento na lista, o prev da sentinela tambem apontara para ele
    else
        l->sentinel->next->prev = newNode; //caso nao seja o unico, o prev do antigo primeiro apontara para o novo primeiro
    l->sentinel->next = newNode;
    l->qty++;
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    newNode->next = l->sentinel;
    newNode->prev = l->sentinel->prev; //o anterior antes do novo eh o antigo prev da sentinela
    if (l->sentinel->prev == l->sentinel) //caso seja o unico elemento na lista, o next da sentinela tambem apontara para ele
        l->sentinel->next = newNode;
    else
        l->sentinel->prev->next = newNode; //caso nao seja o unico, o next do antigo ultimo apontara para o novo primeiro
    l->sentinel->prev = newNode;
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
    if(!emptyList(l)){ //se a lista nao esta vazia
        lastNode->next->prev = lastNode->prev; //aponta prev do primeiro elemento pro penultimo node
        lastNode->prev->next = lastNode->next; //atualiza next do penultimo node
        free(lastNode); //destroi "ultimo node"
        l->qty--;
    }
}

void removeStartList (listaEnc *l) {
    struct node *firstNode = l->sentinel->next; //cria variavel estatica para o sentinela next (ultimo node)
    if (!emptyList(l)) {//se a lista nao esta vazia
        firstNode->next->prev = firstNode->prev; //aponta next do segundo node para o ultimo
        firstNode->prev->next = firstNode->next; //aponta next do ultimo node para o segundo
        free(firstNode); //destroi "primeiro node"
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
    while (!emptyList(l)) //remove enquanto ainda houver elemento
        removeStartList(l);
    free(l->sentinel);
    l->sentinel = NULL;
    l->qty = 0;
}
/* funcoes da lista com iterador */
void insertAfterList (listaEnc* l,iterador i, type data) {
    if (l != i.list) { //o iterador obrigatoriamente precisa ser da mesma lista que a lista apontada nos parametros
        return;         //do contrario, a funcao não ira executar por seguranca
    }
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->prev = i.position;
    newNode->next = i.position->next;
    i.position->next->prev = newNode;
    i.position->next = newNode;
}

void insertBeforeList (listaEnc* l,iterador i, type data) {
    if (l != i.list) { //o iterador obrigatoriamente precisa ser da mesma lista que a lista apontada nos parâmetros
        return;         //do contrario, a funcao nao ira executar por seguranca
    }
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->prev = i.position->prev;
    newNode->next = i.position;
    i.position->prev->next = newNode;
    i.position->prev = newNode;
}

iterador searchFirstList(listaEnc* l , type data) {
    l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
    iterador searchIt = firstElementList(l); //cria um iterador apontando para o inicio da lista
    while (getElementList(searchIt) != data) //avança de posicao até achar o valor procurado
        nextElementList(&searchIt);          //a funcao termina pois em ultimo caso o valor está na propria sentinela
    return searchIt; //retorna o iterador apontando para o elemento procurado ou um iterador apontanto para o fim se nao achar 
}

iterador searchAfterList(listaEnc* l,iterador i, type data) {
    l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
    while (getElementList(i)!= data) //avança searchIt de posição até achar o valor procurado
        nextElementList(&i);          //a funcao termina pois em ultimo caso o valor esta na propria sentinela
    return i; //retorna o iterador apontando para o elemento procurado ou um iterador apontando para o fim se nao achar
}