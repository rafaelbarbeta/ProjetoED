#ifndef LISTA_H

#define LISTA_H
// estruturas da lista encadeada
typedef int type;
typedef struct { //representa a lista em si
    struct node *sentinel;
    unsigned int qty;
} listaEnc;

struct node { // representa um elemento
    struct node *next, *prev;
    type data;
};

// funções da lista encadeada, todas O(1)
void startList (listaEnc *l); //inicia a lista encadeada
int emptyList (listaEnc *l); //verifica se a lista eh vazia, retorna 1 se esta e 0 se não está vazia
void addStartList (listaEnc *l, type num); //insere o parametro "num" no inicio da lista
void addEndList (listaEnc *l, type num); //insere o parametro "num" no fim da lista
void removeStartList (listaEnc *l); //remove do inicio da lista
void removeEndList (listaEnc *l); //remove do fim da lista
unsigned int sizeList (listaEnc *l); //retorna o tamanho
type viewStartList (listaEnc *l); //visualiza o valor type que esta no inicio da lista
type viewEndList (listaEnc *l); //visualiza o valor type que esta no fim da lista
// função de complexidade O(n)
void wreckList (listaEnc *l); //destroi a lista
#endif