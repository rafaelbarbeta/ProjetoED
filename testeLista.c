#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lista.h"

int testeAdicionarRemover() {
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) { //adiciona varios elementos no inicio
        addStartList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
       if (viewStartList(&listaTeste) != i){
            printf("Erro na função testeAdicionarRemover\n");
            wreckList(&listaTeste);
            return 1;
       }
        removeStartList(&listaTeste);
    }
    wreckList(&listaTeste);
    return 0;
}

int testeAdicionarRemoverFim() { //adciona varios elementos no fim
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) {
        addEndList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
       if (viewEndList(&listaTeste) != i){
            printf("Erro na função testeAdicionarRemoverFim\n");
            wreckList(&listaTeste);
            return 1;
       }
        removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
    return 0;
}

int testeMisturadoInicioFim() {
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i += 2) { //os pares estão no início decrescente
        addStartList(&listaTeste,i); //os impares estão no fim de forma crescente
        addEndList(&listaTeste,i+1);
    }
    for (i = 50000; i >= 0; i -= 2) {
        if (viewStartList(&listaTeste) != i) {
            printf("Erro na função testeMisturadoInicioFim\n");
            wreckList(&listaTeste);
            return 1;
        }
        else if (viewEndList(&listaTeste) != i+1) {
            printf("Erro na função testeMisturadoInicioFim\n");
            wreckList(&listaTeste);
            return 1;
        }
        removeStartList(&listaTeste); 
        removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
    return 0;
}

int testeViolacaoMem() {
    listaEnc listaTeste;
    startList(&listaTeste);
    int inicio;
    srand(time(NULL));
    int i;
    for (i = 0; i < 10000;i++) { //adiciona elementos randomicamente tentando ocasionar uma falha de segmentacao
        inicio = rand() % 2;
        if (inicio)
            addStartList(&listaTeste,i);
        else
            addEndList(&listaTeste,i);
    }
    for (i = 0; i < 50000; i++) { //tenta remover mais elementos do que eh possivel, a API deve se proteger disso
        inicio = rand() % 2;
        if (inicio)
            removeStartList(&listaTeste);
        else
            removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
    return 0;
}

int main() {
    int qtdErros = testeAdicionarRemover() + testeAdicionarRemoverFim() + testeMisturadoInicioFim() + testeViolacaoMem();
    if (!qtdErros)
        printf("Todas as funções da lista estão funcionando corretamente\n");
    else
        printf("Erros encontrados!\n");
    printf("Erros : %d\n",qtdErros);
    return 0;
}