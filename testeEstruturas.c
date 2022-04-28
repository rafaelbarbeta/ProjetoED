#include <time.h>
#include <stdlib.h>
#include "lista.h"
#include "listaordenada.h"
#include "deque.h"
#include <check.h>

//testes da lista encadeada
START_TEST(testeAdicionarInicioLista) {
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) { //adiciona vários elementos no inicio
        addStartList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
        ck_assert_int_eq(viewStartList(&listaTeste), i);
        removeStartList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(testeAdicionarFimLista) { 
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) { //adiciona vários elementos no fim
        addEndList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
        ck_assert_int_eq(viewEndList(&listaTeste),i);
        removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(testeMisturadoInicioFimLista) {
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i += 2) { 
        addStartList(&listaTeste,i); //os pares estão no início de forma decrescente
        addEndList(&listaTeste,i+1); //os impares estão no fim de forma crescente
    }
    for (i = 50000; i >= 0; i -= 2) {
        ck_assert_int_eq(viewStartList(&listaTeste),i);
        ck_assert_int_eq(viewEndList(&listaTeste),(i+1));
        removeStartList(&listaTeste); 
        removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(testeViolacaoMemLista) {
    listaEnc listaTeste;
    startList(&listaTeste);
    int inicio;
    srand(time(NULL));
    int i;
    for (i = 0; i < 10000;i++) { //adiciona elementos randomicamente tentando ocasionar uma falha de segmentação
        inicio = rand() % 2;
        if (inicio)
            addStartList(&listaTeste,i);
        else
            addEndList(&listaTeste,i);
    }
    for (i = 0; i < 50000; i++) { //tenta remover mais elementos do que é possivel, a API deve se proteger disso
        inicio = rand() % 2;
        if (inicio)
            removeStartList(&listaTeste);
        else
            removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(poucosElementosLista) {
    listaEnc listaTeste;
    startList(&listaTeste);
    addStartList(&listaTeste,20);
    removeEndList(&listaTeste);
    addEndList(&listaTeste,21);
    addStartList(&listaTeste,80);
    removeEndList(&listaTeste);
    ck_assert_int_eq(viewStartList(&listaTeste),80);
    wreckList(&listaTeste);
}
END_TEST

int compare(int x, int y) {
    if (x > y)
        return 1;
    else
        return -1;
}

int compareQsort(const void * x, const void * y) {
    return *(int*)x - *(int*)y;
}



//Cria a suite da lista encadeada
Suite *criar_lista_suite() {
    Suite *s;
    TCase *tc_lista;
    
    s = suite_create("Teste Lista");
    tc_lista = tcase_create("Teste Lista TCase");
    tcase_add_test(tc_lista,testeAdicionarInicioLista);
    tcase_add_test(tc_lista,testeAdicionarFimLista);
    tcase_add_test(tc_lista,testeMisturadoInicioFimLista);
    tcase_add_test(tc_lista,testeViolacaoMemLista);
    tcase_add_test(tc_lista,poucosElementosLista);
    suite_add_tcase(s,tc_lista);
    return s;
}
//testes do deque
START_TEST(insercaoInicioDeque) {
    deque dequeTeste;
    startDeque(&dequeTeste,10000);
    int i;
    for (i = 1; i <= 10000; i++) { //adiciona vários elementos no inicio
        addStartDeque(&dequeTeste,i);
    }
    for (i = 10000; i >= 1; i--) {
        ck_assert_int_eq(viewStartDeque(&dequeTeste), i);
        removeStartDeque(&dequeTeste);
    }
    wreckDeque(&dequeTeste);
}
END_TEST

START_TEST(insercaoFinalDeque) {
    deque dequeTeste;
    startDeque(&dequeTeste,10000);  
    int i;
    for (i = 1; i <= 10000; i++) { //adiciona vários elementos no inicio
        addEndDeque(&dequeTeste,i);
    }
    for (i = 10000; i >= 1; i--) {
        ck_assert_int_eq(viewEndDeque(&dequeTeste), i);
        removeEndDeque(&dequeTeste);
    }
    wreckDeque(&dequeTeste);
}
END_TEST

START_TEST(insercaoInicioFimDeque) {
    deque dequeTeste;
    startDeque(&dequeTeste,100000);
    int i;
    for (i = 0; i <= 50000; i += 2) { 
        addStartDeque(&dequeTeste,i); //os pares estão no início de forma decrescente
        addEndDeque(&dequeTeste,i+1); //os impares estão no fim de forma crescente
    }
    for (i = 50000; i >= 0; i -= 2) {
        ck_assert_int_eq(viewStartDeque(&dequeTeste),i);
        ck_assert_int_eq(viewEndDeque(&dequeTeste),(i+1));
        removeStartDeque(&dequeTeste); 
        removeEndDeque(&dequeTeste);
    }
}
END_TEST

START_TEST(detecaoFullDeque) {
    deque dequeTeste;
    startDeque(&dequeTeste,10000);
    int i;
    for (i = 0; i < 10000; i++) {
        addStartDeque(&dequeTeste,i);
    }
    int possivel = addStartDeque(&dequeTeste,9);
    ck_assert_int_eq(possivel,0); //error deve ser igual a 1, pois o deque esta cheio
    possivel = addEndDeque(&dequeTeste,9);
    ck_assert_int_eq(possivel,0); //error deve ser igual a 1, pois o deque esta cheio (mesmo adicionando no final)
    removeStartDeque(&dequeTeste);
    possivel = addEndDeque(&dequeTeste,9);
    ck_assert_int_eq(possivel,1); //uma posição foi liberada, o deque deve ser capaz de adicionar elementos agora
    ck_assert_int_eq(viewEndDeque(&dequeTeste),9); //deve ter sido guardado o valor 9 no final do deque
    wreckDeque(&dequeTeste);
}
END_TEST

START_TEST(insercaoRemocaoCircularDeque) {
    deque dequeTeste;
    startDeque(&dequeTeste,10);
    int i;
    for (i = 0; i < 10; i++) { //deque contem os elementos : 0 5 10 15 20 25 30 35 40 45
        addEndDeque(&dequeTeste,(i*5));
    }
    //coloca os elementos do início no final, verificando se o próximo elemento do inicio é o esperado
    //ex, para i = 1, o valor do inicio deve ser 5 (5 10 15 20 25 30 35 40 45 0), já para i = 10, o valor deve ser 0
    //(0 5 10 15 20 25 30 35 40 45)
    for (i = 0; i < 10000; i++) { 
        int valInicio = viewStartDeque(&dequeTeste); 
        ck_assert_int_eq(valInicio,(i%10)*5);
        removeStartDeque(&dequeTeste);
        addEndDeque(&dequeTeste,valInicio);
    }
    wreckDeque(&dequeTeste);
} 
END_TEST

//Suite dos testes do Deque
Suite *criar_deque_suite() {
    Suite *s;
    TCase *tc_deque;
    s = suite_create("Teste Deque");
    tc_deque = tcase_create("Teste Deque TCase");
    tcase_add_test(tc_deque,insercaoInicioDeque);
    tcase_add_test(tc_deque,insercaoFinalDeque);
    tcase_add_test(tc_deque,insercaoInicioFimDeque);
    tcase_add_test(tc_deque,detecaoFullDeque);
    tcase_add_test(tc_deque,insercaoRemocaoCircularDeque);
    suite_add_tcase(s,tc_deque);
    return s;
}

/* testes da lista ordenada */
START_TEST(insercaoOrdenada) {
    listaEncOrd listaOrdenadaTeste;
    int (*funcaoOrdenacao)(int,int); //cria ponteiro de funcao para a ordenacao da lista ordenada
    funcaoOrdenacao = compare;
    startListOrd(&listaOrdenadaTeste,funcaoOrdenacao);
    int vetorTeste[10000]; //vetor com valores de teste
    srand(time(NULL));
    int i;
    for (i = 0; i < 10000; i++) { //adiciona números aleatorios na lista ordenada e no vetor
        int random;
        random = rand() % 10000;
        vetorTeste[i] = random;
        sortedInsertOrd(&listaOrdenadaTeste,random);
    }
    qsort(vetorTeste,10000,sizeof(int),compareQsort); //funcao para ordenar os valores randomicos obtidos no vetor
    iteradorOrd it;
    it = firstElementListOrd(&listaOrdenadaTeste);
    for (i = 0; i < 10000; i++) { //compara o vetor ordenado com a lista e verifica se esta ordenado
        ck_assert_int_eq(getElementListOrd(it),vetorTeste[i]);
        nextElementListOrd(&it);
    }
    wreckListOrd(&listaOrdenadaTeste);
}
END_TEST

Suite *criar_listaOrdenada_suite() {
    Suite *s;
    TCase *tc;
    s = suite_create("Teste Lista Ordenada");
    tc = tcase_create("TCase Lista Ordenada");
    tcase_add_test(tc,insercaoOrdenada);
    suite_add_tcase(s,tc);
    return s;
}

int main() {
    Suite *lista = criar_lista_suite();
    Suite *deque = criar_deque_suite();
    Suite *lista_ordenada = criar_listaOrdenada_suite();
    SRunner *runLista = srunner_create(lista);
    SRunner *runDeque = srunner_create(deque);
    SRunner *runListaOrdenada = srunner_create(lista_ordenada);
    srunner_run_all(runLista,CK_NORMAL);
    srunner_run_all(runDeque,CK_NORMAL);
    srunner_run_all(runListaOrdenada,CK_NORMAL);
    srunner_free(runLista);
    srunner_free(runDeque);
    return 0;
}