#include <stdlib.h>
#include "deque.h"

void startDeque (deque *d, unsigned int size) {
    d->head = 0; //indices iniciados em 0
    d->tail = 0;
    d->imax = size-1;
    d->vect = (type*) malloc (size * sizeof(type));
}
void nextDeque (deque *d, unsigned int *index, int mode) {
    //vai para a proxima posicao normalmente
    if (index > 0 && index != (d->imax)) 
        index = index + mode; //incrementa ou decrementa 1 dependendo do mode

    //se ocorre decremento da posicao 0     
    if (index == 0  && mode == -1) 
        index = (d->imax); //index passa a ser o ultimo
    else    
        (index)++; //se nao, ocorre incremento normalmente

    //se ocorre incremento na utima posicao
    if (index == (d->imax) && mode == 1)
        index = 0; //index retorna ao inicio 0
    else 
        (index)--; //se nao, ocorre decremento normalmente
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
}
