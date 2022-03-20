#include <stdio.h>
#include "deque.h"

int main () {
    deque meuDeque;
    startDeque(&meuDeque,100);
    int i;
    for (i = 0; i < 100; i += 2) {
        addStartDeque(&meuDeque,i);
        addEndDeque(&meuDeque,i+1);
    }
    int valTopo = viewStartDeque(&meuDeque);
    int valFim = viewEndDeque(&meuDeque);
    printf("%d %d",valTopo,valFim);
    return 0;
}