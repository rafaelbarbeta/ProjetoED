#ifndef LISTA_H

#define LISTA_H
// estruturas da lista encadeada
typedef int type;
typedef struct {
    struct node *sentinel;
    unsigned int qty;
    int (*user_compare)(type x, type y); //funcao de comparacao passada pelo usuario para insercao ordenada
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

/*inicia a lista com o sentinela. O usuario deve passar uma funcao de comparacao para insercao ordenada. Essa funcao deve ter como
parametros duas variaveis do tipo type definido no header do arquivo que serao comparadas na insercao ordenada, e deve retornar um inteiro, sendo
que se retorno <= 0, entao o primeiro elemento vem antes do segundo, e para retorno > 0, o primeiro elemento vem depois do segundo.
*/
void startList (listaEnc *l,int (*user_compare)(type x, type y)); 
int emptyList (listaEnc *l); //se a lista esta vazia retorna 1, se nao 0
void removeStartList (listaEnc *l); //remove primeiro elemento da lista
void removeEndList (listaEnc *l); //remove ultimo elemento da lista
unsigned int sizeList (listaEnc *l); //retorna tamanho da lista (quantidade de nodes)
type viewStartList (listaEnc *l); //retorna primeiro elemento da lista (data)
type viewEndList (listaEnc *l); //retorna ultimo elemento da lista (data)
// funcao de complexidade O(n)
void sortedInsert(listaEnc *l, type num); //adiciona um elemento de forma ordenada na lista encadeada utilizando a função user_compare na struct
void wreckList (listaEnc *l); //destroi completamente a lista


//funções que utilizam o iterador
int removeElementList (listaEnc* l,iterador *i); //remove um elemento apontado pelo iterador e avança o iterador uma posição

iterador firstElementList(listaEnc* l); //retorna um iterador apontando para o primeiro elemento da lista
iterador lastElementList(listaEnc* l);  //retorna um iterador apontando para o ultimo elemento da lista

type getElementList(iterador i); //retorna o valor do elemento guardado na posição apontado pelo iterador
int nextElementList(iterador* i); //avanca uma posicao na lista, deve ser passado o endereco do iterador
int previousElementList(iterador* i); //retorna uma posicao na lista, deve ser passado o endereço do iterador
int endList(iterador i); //verifica se a lista acabou

// funções de complexidade O(n)
iterador searchFirstList(listaEnc* l , type data); //procura um elemento apartir da primeira posicao da lista
iterador searchAfterList(listaEnc* l,iterador i, type data); //procura um elemento apartir da posicao apontada pelo iterador
iterador searchPositionList(listaEnc* l, unsigned int position); //retorna um iterador apontando para o elemento na posicao especificada "position"
                                                                //0 é a posicao do primeiro elemento
#endif