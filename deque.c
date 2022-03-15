#include <stdlib.h>
#include "deque.h"

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