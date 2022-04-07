#include <stdlib.h>
#include "deque.h"
int startDeque (deque *d, unsigned int size) {
    d->head = 0; //índices iniciados em 0
    d->tail = 0;
    d->imax = size; 
    d->vect = (type*) malloc ((size+1)* sizeof(type)); //aloca uma posição extra para ajudar nas operações do deque (empty e full)
    if (d->vect == NULL) //significa que não há mais memória no sistema. Retorna 0 para o usuário para indicar falha
        return 0;
    return 1;
}
void nextDeque (deque *d, unsigned int *index, int mode) {
    //caso o index não esteja "nos extremos do vetor" vai para a próxima posição normalmente
    if (*index != 0 && *index != (d->imax)) {
        *index = *index + mode; //incrementa ou decrementa 1 dependendo do mode
    }
    // caso esteja no inicio e mode = -1, vai pro final do vetor, se não, aumenta 1
    else if (*index == 0) { 
        if (mode == -1) 
            *index = d->imax;
        else
            (*index)++;
    }
    //caso esteja no final e mode = 1, vai para o início, se não, diminui 1
    else {
        if (mode == 1)
            *index = 0;
        else
            (*index)--;
    }
}

int addStartDeque (deque *d, type num) {
    if (!fullDeque(d)) { //verifica se o deque não está cheio
        d->vect[d->head] = num; //adiciona o valor no deque
        nextDeque(d,&(d->head),1); //avança uma posição no vect circularmente
        return 1;
    }
    return 0;
}

int addEndDeque (deque *d, type num) {
    if (!fullDeque(d)) { //verifica se o deque não está cheio
        nextDeque(d,&(d->tail),-1); //retrocede uma posição no vect circularmente
        d->vect[d->tail] = num; //adiciona o valor no deque
        return 1;
    }
    return 0;
}

type viewStartDeque (deque *d) {
    //copia-se o valor da head na variável indexTemp, retrocede esse indexTemp em uma posição e
    //o resultado é o início do deque. A head permanece inalterada depois dessa alteração
    unsigned int indexTemp = d->head; 
    nextDeque(d,&indexTemp,-1);
    return d->vect[indexTemp];
}

type viewEndDeque (deque *d) {
    return d->vect[d->tail]; // a tail já aponta para o último valor, e não para o próximo local disponível
}

void wreckDeque (deque *d) {
    free(d->vect); //libera vetor
    d->vect = NULL; //o ponteiro passa a apontar para NULL (evita dangling pointer)
    d->head = 0;
    d->tail = 0;
    d->imax = 0;
}

int emptyDeque (deque *d){
    return d->head == d->tail ? 1 : 0; //se head == tail entao o deque está vazio
}

int fullDeque (deque *d){
    unsigned int indexTemp = d->tail; //cria um index temporario que recebe o valor de tail
    //retroce uma posicao do index temporario e verifica se head e tail são iguais. Se forem, então o deque está cheio
    nextDeque(d,&indexTemp,-1);
    if (indexTemp == d->head)
        return 1;
    else
        return 0;
}
int removeStartDeque (deque *d){
    if (!emptyDeque(d)) { //para remover um elemento no início, basta deslocar head uma posição para trás circularmente 
        nextDeque(d,&(d->head),-1);
        return 1;
    }
    return 0;
}
int removeEndDeque (deque *d){
    if (!emptyDeque(d)) { //para remover um elemento no inicio, basta deslocar tail uma posição para frente circularmente
        nextDeque(d,&(d->tail),1);
        return 1;
    }
     return 0;
}