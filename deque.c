#include <stdlib.h>
#include "deque.h"

void startDeque (deque *d, unsigned int size) {
    d->head = 0; //indices iniciados em 0
    d->tail = 0;
    d->imax = size; 
    d->vect = (type*) malloc ((size+1)* sizeof(type)); //aloca uma posicao extra para ajudar nas operacoes do deque (empty e full)
}
void nextDeque (deque *d, unsigned int *index, int mode) {
    //caso o index nao esteja "nos extremos do vetor" vai para a proxima posicao normalmente
    if (*index != 0 && *index != (d->imax)) {
        *index = *index + mode; //incrementa ou decrementa 1 dependendo do mode
    }
    // caso esteja no inicio e mode = -1, vai pro final do vetor, se nao, aumenta 1
    else if (*index == 0) { 
        if (mode == -1) 
            *index = d->imax;
        else
            (*index)++;
    }
    //caso esteja no final e mode = 1, vai para o inicio, se nao, diminui 1
    else {
        if (mode == 1)
            *index = 0;
        else
            (*index)--;
    }
}

int addStartDeque (deque *d, type num) {
    if (!fullDeque(d)) { //verifica se o deque nao esta cheio
        d->vect[d->head] = num; //adiciona o valor no deque
        nextDeque(d,&(d->head),1); //avanca uma posicao no vect circularmente
        return 1;
    }
    return 0;
}

int addEndDeque (deque *d, type num) {
    if (!fullDeque(d)) { //verifica se o deque nao esta cheio
        nextDeque(d,&(d->tail),-1); //retrocede uma posicao no vect circularmente
        d->vect[d->tail] = num; //adiciona o valor no deque
        return 1;
    }
    return 0;
}

type viewStartDeque (deque *d) {
    //copia-se o valor da head na variavel indexTemp, retroce esse indexTemp em uma posicao e
    //o resultado eh o inicio do deque. A head permanece inalterada depois dessa alteracao
    unsigned int indexTemp = d->head; 
    nextDeque(d,&indexTemp,-1);
    return d->vect[indexTemp];
}

type viewEndDeque (deque *d) {
    return d->vect[d->tail]; // a tail ja aponta para o ultimo valor, e nao para o proximo local disponivel
}

void wreckDeque (deque *d) {
    free(d->vect); //libera vetor
    d->vect = NULL; //o ponteiro passa a apontar para NULL (evita dangling pointer)
    d->head = 0;
    d->tail = 0;
    d->imax = 0;
}