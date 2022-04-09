#include "listaordenada.h"
#include <stdlib.h>

/* funções da lista sem iterador*/
void startList (listaEnc *l,int (*user_compare)(type x, type y)) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node)); //constroi o node sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para si mesmo no next e prev
    l->sentinel->prev = l->sentinel;
    l->user_compare = user_compare; //guarda o endereco da funcao de comparacao definida pelo usuario
}

void sortedInsert(listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = num;
    if(emptyList(l)) { // se a lista estiver vazia, apenas insere no inicio normalmente
        newNode->next = l->sentinel->next; //o próximo depois do novo no é o antigo next da sentinela
        newNode->prev = l->sentinel; //a anterior é a propria sentinela
        l->sentinel->next->prev = newNode; //o prev do antigo primeiro (ou a sentinela) recebe o endereço do novo node
        l->sentinel->next = newNode; //o next da sentinela aponta para o início da lista, no caso, o novo node
        l->qty++;
        return;
    }
    iterador i;
    /*percorre-se toda a lista procurando onde o elemento deve ser inserido para que a lista continue ordenada.
    para isso, caso "num" venha antes da posicao apontada pelo iterador i, sabemos que "num" deve ser inserido imediatamente
    antes dessa posicao apontada por i, pois i vem depois de todos os valores ja percorridos, mas vem antes desse valor.
    */
    for (i = firstElementList(l); !endList(i); nextElementList(&i)) {
        if (l->user_compare(num,getElementList(i)) <= 0) { 
            newNode->next = i.position; //realiza uma insercao entre o elemento apontado por i e seu antecessor
            newNode->prev = i.position->prev;
            i.position->prev->next = newNode;
            i.position->prev = newNode;
            l->qty++;
            return; 
        }
    }
    //caso "num" venha depois de todos os elementos da lista, entao deve ocorrer uma insercao no final
    //o loop for nao ira inseririr o elemento em nenhum momento se esse for o caso, que eh o pior em termos de complexidade
    newNode->next = l->sentinel; //o próximo depois do novo é a própria sentinela
    newNode->prev = l->sentinel->prev; //o anterior antes do novo é o antigo prev da sentinela
    l->sentinel->prev->next = newNode; //caso não seja o único, o next do antigo último apontara para o novo primeiro
    l->sentinel->prev = newNode; //o prev da sentinela aponta para o último da lista, no caso, o novo node
    l->qty++;
    return;
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