#include "lista.h"
#include <stdlib.h>

/* funções da lista sem iterador*/
void startList (listaEnc *l) {
    l->qty = 0;
    l->sentinel = (struct node*) malloc(sizeof(struct node)); //constroi o node sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para si mesmo no next e prev
    l->sentinel->prev = l->sentinel;
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

void addStartList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    if(newNode!=NULL){ //verifica se a memoria esta cheia, nesse caso ira apontar pra NULL, sendo assim nao ira adicionar nenhum valor na lista
        newNode->data = num;
        newNode->next = l->sentinel->next; //o proximo depois do novo no eh o antigo next da sentinela
        newNode->prev = l->sentinel; //a anterior eh a propria sentinela
        l->sentinel->next->prev = newNode; //o prev do antigo primeiro (ou a sentinela) recebe o endereco do novo node
        l->sentinel->next = newNode; //o next da sentinela aponta para o início da lista, no caso, o novo node
        l->qty++;
    }
}

void addEndList (listaEnc *l, type num) {
    struct node* newNode = malloc(sizeof(struct node));
    if(newNode!=NULL){//verifica se a memoria esta cheia, nesse caso ira apontar pra NULL, sendo assim nao ira adicionar nenhum valor na lista
        newNode->data = num;
        newNode->next = l->sentinel; //o proximo depois do novo eh a propria sentinela
        newNode->prev = l->sentinel->prev; //o anterior antes do novo eh o antigo prev da sentinela
        l->sentinel->prev->next = newNode; //caso nao seja o unico, o next do antigo último apontara para o novo primeiro
        l->sentinel->prev = newNode; //o prev da sentinela aponta para o ultimo da lista, no caso, o novo node
        l->qty++;
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

void removeEndList (listaEnc *l){
    struct node *lastNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(!emptyList(l)){ //se a lista nao esta vazia
        lastNode->next->prev = lastNode->prev; //aponta prev do primeiro elemento pro penultimo node
        lastNode->prev->next = lastNode->next; //atualiza next do penultimo node
        free(lastNode); //destroi "ultimo node"
        l->qty--;
    }
}

unsigned int sizeList (listaEnc *l) {
    return (l->qty); //retorna qtd nodes
}

type viewStartList (listaEnc *l) {
    if(!emptyList(l)){ //se a lista nao esta vazia
        return (l->sentinel->next->data); //retorna data do posterior ao sentinela
    }
}

type viewEndList (listaEnc *l) {
    if(!emptyList(l)){//se a lista nao esta vazia
        return (l->sentinel->prev->data); //retorna data do anterior ao sentinela
    }
}

//operacao de complexidade O(n)
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

int removeElementList (listaEnc* l,iterador *i){
    if(!endList(*i)){
        struct node* nextElement = i->position->next; //guarda o endereco do proximo e do anterior ao node apontado pelo iterador
        struct node* prevElement = i->position->prev;
        free(i->position); //efetivamente apaga o elemento da lista
        nextElement->prev = prevElement; //atualiza os ponteiros
        prevElement->next = nextElement;
        i->position = nextElement; // avanca o iterador em uma posicao para que ele nao aponte para um elemento invalido
        l->qty--;
        return 1;
    }
    return 0; // a operacao falhou
}

iterador firstElementList(listaEnc* l) {
    iterador i; 
    i.list = l;
    i.position = l->sentinel->next; // se a lista estiver vazia, aponta para sentinel
    return (i); 
}

iterador lastElementList(listaEnc* l) {
    iterador i;
    i.list = l;
    i.position = l->sentinel->prev; // se a lista estiver vazia, aponta para sentinel
    return (i); 
}

type getElementList(iterador i){
    if(!endList(i)){ //verifica se nao acabou a lista pois caso tenha acabado ira apontar para um endereco invalido
        return i.position->data;
    }
    else{
        return 0;
    }
}

int nextElementList(iterador* i) {
    if (!emptyList(i->list)) { //a lista precisa ter algum elemento
        i->position = i->position->next; //atualiza iterador para o proximo elemento
        return (1);
    }
    else return(0); //funcao nao executada
}

int previousElementList(iterador* i) {
    if (!emptyList(i->list)) { //a lista precisa ter algum elemento
        i->position = i->position->prev; //atualiza iterador para o elemento anterior
        return (1);
    }
    else return (0); //funcao nao executada
}

int endList(iterador i){
    return i.position == i.list->sentinel; //retorna verdadeiro caso a lista tenha acabado
}
//operacoes de complexidade O(n)
iterador searchFirstList(listaEnc* l , type data) {
    if(!emptyList(l)){
        l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
        iterador searchIt = firstElementList(l); //cria um iterador apontando para o inicio da lista
        while (getElementList(searchIt) != data) //avanca de posicao ate achar o valor procurado
            nextElementList(&searchIt);          //a funcao termina pois em ultimo caso o valor esta na propria sentinela
        return searchIt; //retorna o iterador apontando para o elemento procurado ou um iterador apontanto para o fim se nao achar 
    }
}

iterador searchAfterList(listaEnc* l,iterador i, type data) {
    if(!emptyList(l)){
        l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
        while (getElementList(i)!= data) //avança searchIt de posição até achar o valor procurado
            nextElementList(&i);          //a funcao termina pois em ultimo caso o valor esta na propria sentinela
        return i; //retorna o iterador apontando para o elemento procurado ou um iterador apontando para o fim se nao achar
    }
}

iterador searchPositionList(listaEnc* l, unsigned int position) {
    if(!emptyList(l)){//se a lista nao estiver vazia
        iterador i;
        i = firstElementList(l); // obtem um iterador apontando para o inicio da lista
        while (position != 0) { // avanca o iterador ate chegar na posicao
            if (endList(i)) //caso chegue no fim da lista, retorna o iterador apontando para sentinel (endList)
                return i;
            i.position = i.position->next;
            position--;
        }
        return i; //retorna o iterador apontando para o elemento desejado
    }
}

