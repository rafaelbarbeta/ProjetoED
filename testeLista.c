#include <stdio.h>
#include "lista.h"
int main() {
    listaEnc Lista;
    startList(&Lista);

    addStartList(&Lista, 4);
    addStartList(&Lista, 3);
    addStartList(&Lista, 2);
    printf("%i\n", viewStartList(&Lista));
    printf("%i\n", viewEndList(&Lista));
    wreckList(&Lista);
}