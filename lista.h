#ifndef LISTA_H

#define LISTA_H
// estruturas da lista encadeada
typedef int type;
typedef struct {
    struct node *sentinel;
    unsigned int qty;
} listaEnc;

struct node {
    struct node *next, *prev;
    type data;
};
// estrutura do iterador

typedef struct  {
    listaEnc *list;
    struct node *position;
} iterador;

// funcoes da lista encadeada
void startList (listaEnc *l); //inicia a lista com o sentinela
int emptyList (listaEnc *l); //se a lista esta vazia retorna 1, se nao 0
void addStartList (listaEnc *l, type num); //insere elemento "num" no inicio da lista
void addEndList (listaEnc *l, type num); //insere elemento "num" no final da lista
void removeStartList (listaEnc *l); //remove primeiro elemento da lista
void removeEndList (listaEnc *l); //remove ultimo elemento da lista
unsigned int sizeList (listaEnc *l); //retorna tamanho da lista (quantidade de nodes)
type viewStartList (listaEnc *l); //retorna primeiro elemento da lista (data)
type viewEndList (listaEnc *l); //retorna ultimo elemento da lista (data)
// funcao de complexidade O(n)
void wreckList (listaEnc *l); //destroi completamente a lista


//funcoes que utilizam o iterador
void insertAfterList (listaEnc* l,iterador i, type data); //insere um elemento depois do elemento apontado pelo iterador
void insertBeforeList (listaEnc* l,iterador i, type data); //insere um elemento antes do elemento apontado pelo iterador
int removeElementList (listaEnc* l,iterador *i); //remove um elemento apontado pelo iterador e avança o iterador uma posição

iterador firstElementList(listaEnc* l); //retorna um iterador apontando para o primeiro elemento da lista
iterador lastElementList(listaEnc* l);  //retorna um iterador apontando para o ultimo elemento da lista

type getElementList(iterador i); //retorna o valor do elemento guardado na posicao apontado pelo iterador
int nextElementList(iterador* i); //avanca uma posicao na lista, deve ser passado o endereco do iterador
int previousElementList(iterador* i); //retorna uma posicao na lista, deve ser passado o endereço do iterador
int endList(iterador i); //verifica se a lista acabou

// funcoes de complexidade O(n)
iterador searchFirstList(listaEnc* l , type data); //procura um elemento apartir da primeira posicao da lista
iterador searchAfterList(listaEnc* l,iterador i, type data); //procura um elemento apartir da posicao apontada pelo iterador
iterador searchPositionList(listaEnc* l, unsigned int position); //retorna um iterador apontando para o elemento na posicao especificada "position"
                                                                //0 eh a posicao do primeiro elemento
#endif