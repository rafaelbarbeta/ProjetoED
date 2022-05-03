#include "listaordenada.h"
#include <stdlib.h>

/* funcoes da lista sem iteradorOrd*/
void startListOrd (listaEncOrd *l,int (*user_compare)(typeOrd x, typeOrd y)) {
    l->qty = 0;
    l->sentinel = (struct nodeOrd*) malloc(sizeof(struct nodeOrd)); //constroi o node sentinela
    l->sentinel->next = l->sentinel; //faz a sentinela apontar para si mesmo no next e prev
    l->sentinel->prev = l->sentinel;
    l->user_compare = user_compare; //guarda o endereco da funcao de comparacao definida pelo usuario
}

int emptyListOrd (listaEncOrd *l){
    struct nodeOrd *newNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(newNode==l->sentinel){ //se essa variavel for igual ao sentinel significa que a lista esta vazia
        return 1; //esta vazia
    }
    else{ //caso contrario significa que a lista nao esta vazia
        return 0;
    }
}

void removeStartListOrd (listaEncOrd *l) {
    struct nodeOrd *firstNode = l->sentinel->next; //cria variavel estatica para o sentinela next (ultimo node)
    if (!emptyListOrd(l)) {//se a lista nao esta vazia
        firstNode->next->prev = firstNode->prev; //aponta next do segundo node para o ultimo
        firstNode->prev->next = firstNode->next; //aponta next do ultimo node para o segundo
        free(firstNode); //destroi "primeiro node"
        l->qty--;
    }
}

void removeEndListOrd (listaEncOrd *l){
    struct nodeOrd *lastNode = l->sentinel->prev; //cria uma variavel estatica que recebe sentinel prev
    if(!emptyListOrd(l)){ //se a lista nao esta vazia
        lastNode->next->prev = lastNode->prev; //aponta prev do primeiro elemento pro penultimo node
        lastNode->prev->next = lastNode->next; //atualiza next do penultimo node
        free(lastNode); //destroi "ultimo node"
        l->qty--;
    }
}

unsigned int sizeListOrd (listaEncOrd *l) {
    return (l->qty); //retorna qtd nodes
}

typeOrd viewStartListOrd (listaEncOrd *l) {
    if(!emptyListOrd(l)){ //verifica se a lista nao esta vazia
        return (l->sentinel->next->data); //retorna data do posterior ao sentinela
    }
}

typeOrd viewEndListOrd (listaEncOrd *l) {
    if(!emptyListOrd(l)){ //verifica se a lista nao esta vazia
        return (l->sentinel->prev->data); //retorna data do anterior ao sentinela 
    }
}
/* funcoes de complexidade O(n) */
void sortedInsertOrd(listaEncOrd *l, typeOrd num) {
    struct nodeOrd* newNode = malloc(sizeof(struct nodeOrd));
    newNode->data = num;
    if(emptyListOrd(l)) { // se a lista estiver vazia, apenas insere no inicio normalmente
        newNode->next = l->sentinel->next; //o proximo depois do novo no eh o antigo next da sentinela
        newNode->prev = l->sentinel; //a anterior eh a propria sentinela
        l->sentinel->next->prev = newNode; //o prev do antigo primeiro (ou a sentinela) recebe o endereço do novo node
        l->sentinel->next = newNode; //o next da sentinela aponta para o início da lista, no caso, o novo node
        l->qty++;
        return;
    }
    iteradorOrd i;
    /*percorre-se toda a lista procurando onde o elemento deve ser inserido para que a lista continue ordenada.
    para isso, caso "num" venha antes da posicao apontada pelo iteradorOrd i, sabemos que "num" deve ser inserido imediatamente
    antes dessa posicao apontada por i, pois i vem depois de todos os valores ja percorridos, mas vem antes desse valor.
    */
    for (i = firstElementListOrd(l); !endListOrd(i); nextElementListOrd(&i)) {
        if (l->user_compare(num,getElementListOrd(i)) <= 0) { 
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

void wreckListOrd (listaEncOrd *l) {
    while (!emptyListOrd(l)) //remove enquanto ainda houver elemento
        removeStartListOrd(l);
    free(l->sentinel);
    l->sentinel = NULL;
    l->qty = 0;
}



/* funcoes da lista com iteradorOrd */

int removeElementListOrd (listaEncOrd* l,iteradorOrd *i){
    if(!endListOrd(*i)){
        struct nodeOrd* nextElement = i->position->next; //guarda o endereco do proximo e do anterior ao node apontado pelo iteradorOrd
        struct nodeOrd* prevElement = i->position->prev;
        free(i->position); //efetivamente apaga o elemento da lista
        nextElement->prev = prevElement; //atualiza os ponteiros
        prevElement->next = nextElement;
        i->position = nextElement; // avanca o iteradorOrd em uma posicao para que ele nao aponte para um elemento invalido
        l->qty--;
        return 1;
    }
    return 0; // a operacao falhou
}

iteradorOrd firstElementListOrd(listaEncOrd* l) {
    iteradorOrd i; 
    i.list = l;
    i.position = l->sentinel->next; // se a lista estiver vazia, aponta para sentinel
    return (i); 
}

iteradorOrd lastElementListOrd(listaEncOrd* l) {
    iteradorOrd i;
    i.list = l;
    i.position = l->sentinel->prev; // se a lista estiver vazia, aponta para sentinel
    return (i); 
}

typeOrd getElementListOrd(iteradorOrd i){
    if(!endListOrd(i)){ //verifica se nao acabou a lista pois caso tenha acabado ira apontar para um endereco invalido
        return i.position->data;
    }
    else{
        return 0;
    }
}

int nextElementListOrd(iteradorOrd* i) {
    if (!endListOrd(*i)) { //a lista precisa ter algum elemento
        i->position = i->position->next; //atualiza iteradorOrd para o proximo elemento
        return (1);
    }
    else return(0); //funcao nao executada
}

int previousElementListOrd(iteradorOrd* i) {
    if (!endListOrd(*i)) { //a lista precisa ter algum elemento
        i->position = i->position->prev; //atualiza iteradorOrd para o elemento anterior
        return (1);
    }
    else return (0); //funcao nao executada
}

int endListOrd(iteradorOrd i){
    return i.position == i.list->sentinel; //retorna verdadeiro caso a lista tenha acabado
}

iteradorOrd searchFirstListOrd(listaEncOrd* l , typeOrd data) {
    if(!emptyListOrd(l)){
        l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
        iteradorOrd searchIt = firstElementListOrd(l); //cria um iteradorOrd apontando para o inicio da lista
        while (getElementListOrd(searchIt) != data) //avança de posicao até achar o valor procurado
            nextElementListOrd(&searchIt);          //a funcao termina pois em ultimo caso o valor está na propria sentinela
        return searchIt; //retorna o iteradorOrd apontando para o elemento procurado ou um iteradorOrd apontanto para o fim se nao achar 
    }
}

iteradorOrd searchAfterListOrd(listaEncOrd* l,iteradorOrd i, typeOrd data) {
    if(!emptyListOrd(l)){//verifica se a lista nao esta vazia
        l->sentinel->data = data; //coloca o valor a ser procurado na sentinela
        while (getElementListOrd(i)!= data) //avança searchIt de posição até achar o valor procurado
            nextElementListOrd(&i);          //a funcao termina pois em ultimo caso o valor esta na propria sentinela
        return i; //retorna o iteradorOrd apontando para o elemento procurado ou um iteradorOrd apontando para o fim se nao achar
    }
}

iteradorOrd searchPositionListOrd(listaEncOrd* l, unsigned int position) {
    if(!emptyListOrd(l)){ //verifica se a lista nao esta vazia
        iteradorOrd i;
        i = firstElementListOrd(l); // obtem um iteradorOrd apontando para o inicio da lista
        while (position != 0) { // avanca o iteradorOrd ate chegar na posicao
            if (endListOrd(i)) //caso chegue no fim da lista, retorna o iteradorOrd apontando para sentinel (endList)
                return i;
            i.position = i.position->next;
            position--;
        }
        return i; //retorna o iteradorOrd apontando para o elemento desejado
    }
}