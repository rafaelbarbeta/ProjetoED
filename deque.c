#include "deque.h"
#include <sdlib.h>

int adicionaInicio (type *deque, type num) {
    if (!cheio(deque)) {
        deque->vet[deque->head] = num;
        proximo(deque,&deque->head);
        return 1;
    }
    return 0;
}

int adicionaFinal (type *deque, type num) {
    if (!cheio(deque)) {
        deque->vet[deque->tail] = num;
        proximo(deque,&deque->tail);
        return 1;
    }
    return 0;
}
