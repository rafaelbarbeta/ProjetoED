#include <time.h>
#include <stdlib.h>
#include "lista.h"
#include <check.h>

START_TEST(testeAdicionarInicio) {
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) { //adiciona varios elementos no inicio
        addStartList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
        ck_assert_int_eq(viewStartList(&listaTeste), i);
        removeStartList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(testeAdicionarFim) { 
    listaEnc listaTeste;
    startList(&listaTeste);
    int i;
    for (i = 0; i <= 50000; i++) { //adiciona varios elementos no fim
        addEndList(&listaTeste,i);
    }
    for (i = 50000; i >= 0; i--) {
        ck_assert_int_eq(viewEndList(&listaTeste),i);
        removeEndList(&listaTeste);
    }
    wreckList(&listaTeste);
}
END_TEST

START_TEST(testeMisturadoInicioFim) {
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

START_TEST(testeViolacaoMem) {
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
}
END_TEST

START_TEST(poucosElementos) {
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

Suite *criar_lista_suite() {
    Suite *s;
    TCase *tc_lista;
    
    s = suite_create("Teste Lista");
    tc_lista = tcase_create("Teste Lista TCase");
    tcase_add_test(tc_lista,testeAdicionarInicio);
    tcase_add_test(tc_lista,testeAdicionarFim);
    tcase_add_test(tc_lista,testeMisturadoInicioFim);
    tcase_add_test(tc_lista,testeViolacaoMem);
    tcase_add_test(tc_lista,poucosElementos);
    suite_add_tcase(s,tc_lista);
    return s;
}

int main() {
    Suite *s = criar_lista_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr,CK_NORMAL);
    srunner_free(sr);
    return 0;
}