#ifndef LISTAORD_H

#define LISTAORD_H
// estruturas da lista encadeada ordenada
typedef int typeOrd;
typedef struct {
    struct nodeOrd *sentinel;
    unsigned int qty;
    int (*user_compare)(typeOrd x, typeOrd y); //funcao de comparacao passada pelo usuario para insercao ordenada
} listaEncOrd;

struct nodeOrd {
    struct nodeOrd *next, *prev;
    typeOrd data;
};
// estrutura do iteradorOrd

typedef struct  {
    listaEncOrd *list;
    struct nodeOrd *position;
} iteradorOrd;

// funções da lista encadeada

/*inicia a lista com o sentinela. O usuario deve passar uma funcao de comparacao para insercao ordenada. Essa funcao deve ter como
parametros duas variaveis do tipo type definido no header do arquivo que serao comparadas na insercao ordenada, e deve retornar um inteiro, sendo
que se retorno <= 0, entao o primeiro elemento vem antes do segundo, e para retorno > 0, o primeiro elemento vem depois do segundo.
*/
void startListOrd (listaEncOrd *l,int (*user_compare)(typeOrd x, typeOrd y)); 
int emptyListOrd (listaEncOrd *l); //se a lista esta vazia retorna 1, se nao 0
void removeStartListOrd (listaEncOrd *l); //remove primeiro elemento da lista
void removeEndListOrd (listaEncOrd *l); //remove ultimo elemento da lista
unsigned int sizeListOrd (listaEncOrd *l); //retorna tamanho da lista (quantidade de nodes)
typeOrd viewStartListOrd (listaEncOrd *l); //retorna primeiro elemento da lista (data)
typeOrd viewEndListOrd (listaEncOrd *l); //retorna ultimo elemento da lista (data)
// funcao de complexidade O(n)
void sortedInsertOrd(listaEncOrd *l, typeOrd num); //adiciona um elemento de forma ordenada na lista encadeada utilizando a função user_compare na struct
void wreckListOrd (listaEncOrd *l); //destroi completamente a lista


//funcoes que utilizam o iteradorOrd
int removeElementListOrd(listaEncOrd* l,iteradorOrd *i); //remove um elemento apontado pelo iteradorOrd e avanca o iteradorOrd uma posicao

iteradorOrd firstElementListOrd(listaEncOrd* l); //retorna um iteradorOrd apontando para o primeiro elemento da lista
iteradorOrd lastElementListOrd(listaEncOrd* l);  //retorna um iteradorOrd apontando para o ultimo elemento da lista

typeOrd getElementListOrd(iteradorOrd i); //retorna o valor do elemento guardado na posicao apontado pelo iteradorOrd
int nextElementListOrd(iteradorOrd* i); //avanca uma posicao na lista, deve ser passado o endereco do iteradorOrd
int previousElementListOrd(iteradorOrd* i); //retorna uma posicao na lista, deve ser passado o endereco do iteradorOrd
int endListOrd(iteradorOrd i); //verifica se a lista acabou

// funcoes de complexidade O(n)
iteradorOrd searchFirstListOrd(listaEncOrd* l , typeOrd data); //procura um elemento apartir da primeira posicao da lista
iteradorOrd searchAfterListOrd(listaEncOrd* l,iteradorOrd i, typeOrd data); //procura um elemento apartir da posicao apontada pelo iteradorOrd
iteradorOrd searchPositionListOrd(listaEncOrd* l, unsigned int position); //retorna um iteradorOrd apontando para o elemento na posicao especificada "position"
                                                                //0 eh a posicao do primeiro elemento
#endif