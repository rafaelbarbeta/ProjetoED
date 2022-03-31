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

// funções da lista encadeada
void startList (listaEnc *l); //inicia
int emptyList (listaEnc *l); //vazio
void addStartList (listaEnc *l, type num); //inserir (inicio)
void addEndList (listaEnc *l, type num); //inseri (final)
void removeStartList (listaEnc *l); //remove (inicio)
void removeEndList (listaEnc *l); //remove (final)
unsigned int sizeList (listaEnc *l); //tamanho
type viewStartList (listaEnc *l); //visualizar (inicio)
type viewEndList (listaEnc *l); //visualizar (final)
// função de complexidade O(n)
void wreckList (listaEnc *l); //destroi


//funções que utilizam o iterador
void insertAfterList (listaEnc* l,iterador i, type data); //insere um elemento depois do elemento apontado pelo iterador
void insertBeforeList (listaEnc* l,iterador i, type data); //insere um elemento antes do elemento apontado pelo iterador
int removeElementList (listaEnc* l,iterador *i); //remove um elemento apontado pelo iterador
iterador firstElementList(listaEnc* l); //retorna um iterador apontando para o primeiro elemento da lista
iterador lastElementList(listaEnc* l);  //retorna um iterador apontando para o ultimo elemento da lista
type getElementList(iterador i); //retorna o valor do elemento guardado na posição apontado pelo iterador
int nextElementList(iterador* i); //avança uma posição na lista, deve ser passado o endereço do iterador
int previousElementList(iterador* i); //retorna uma posição na lista, deve ser passado o endereço do iterador
int endList(iterador i); //verifica se a lista acabou

// funções de complexidade O(n)
iterador searchFirstList(listaEnc* l , type data); //procura um elemento apartir da primeira posição da lista
iterador searchAfterList(listaEnc* l,iterador i, type data); //procura um elemento apartir da posição apontada pelo iterador
iterador searchPositionList(listaEnc* l, unsigned int position); //retorna um iterador apontando para o elemento na posição especificada "position"
                                                                //0 é a posição do primeiro elemento
#endif