#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lista.h"
#include "deque.h"

void inicializar(listaEnc *texto, deque *chave,int modo);
char criptografarCaractere(char chartexto,char charchave);
char descriptografarCaractere(char chartexto,char charchave);

int main () {
    printf("\t\t\tCifra De Vigenère : Versão de Terminal\n");
    printf("Selecione uma opção:\n");
    printf("C : Criptografar texto\n");
    printf("D : Descriptografar texto\n");
    printf("E : Sair do programa\n");
    char option = 0;
    do {
        scanf(" %c",&option);
        switch(option) {
            case 'C' : {
                listaEnc textoPuro;
                deque chave; 
                inicializar(&textoPuro,&chave,1);
                //trecho de criptografia
                printf("O texto criptografado é:\n");
                iterador i;
                // Complexidade O(n)
                for (i = firstElementList(&textoPuro); !endList(i); nextElementList(&i)) {
                    char charchave;
                    char chartexto;
                    char caractereCrip;
                    charchave = viewStartDeque(&chave);
                    chartexto = getElementList(i);
                    caractereCrip = criptografarCaractere(charchave,chartexto);
                    printf("%c",caractereCrip);
                    removeStartDeque(&chave);
                    addEndDeque(&chave,charchave);
                }
                wreckList(&textoPuro);
                wreckDeque(&chave);
            }
            break;
            case 'D' : {
                listaEnc textoPuro;
                deque chave;   
                inicializar(&textoPuro,&chave,0);
                //trecho para descriptografar
                printf("O texto descriptografado é:\n");
                iterador i;
                for (i = firstElementList(&textoPuro); !endList(i); nextElementList(&i)) {
                    char charchave;
                    char chartexto;
                    char caractereDecrip;
                    charchave = viewStartDeque(&chave);
                    chartexto = getElementList(i);
                    caractereDecrip = descriptografarCaractere(chartexto,charchave);
                    printf("%c",caractereDecrip);
                    removeStartDeque(&chave);
                    addEndDeque(&chave,charchave);
                }
                wreckList(&textoPuro);
                wreckDeque(&chave);
            break;
            }
            case 'E' : return 0;
            default : printf("Opção Inválida!\n"); option = 0; break;
        }
    } while (!option);
}

void inicializar(listaEnc *texto, deque *chave,int modo) {
    char proxLetra = 0;
    startList(texto);
    startDeque(&chave,100);
    modo ? printf("Por favor digite um texto para CRIPTOGRAFAR:\n") : printf("Por favor digite um texto para DESCRIPTOGRAFAR:\n");
    while (proxLetra != '\n') {
        scanf(" %c",&proxLetra);
        addEndList(texto,proxLetra);
    }
    removeEndList(texto);
    proxLetra = 0;
    printf("Insira uma chave contendo apenas letras (máximo de 100):\n");
    while (proxLetra != '\n') {
        scanf(" %c",&proxLetra);
        addEndDeque(chave,proxLetra);
    }
    removeEndDeque(chave);    
}

char criptografarCaractere(char chartexto,char charchave) {
    if (!isalpha(chartexto)) { //a função não irá criptografar texto que não é alfabético
        return chartexto;
    }
    //a função de criptografia irá processar todos os caracteres como se fossem minúsculos, para facilidade de código
    //por isso, é necessário guardar se o caractere no texto original era maiúsculo ou não
    int eraMaiusculo = 0;
    if (isupper(chartexto))
        eraMaiusculo = 1;
    chartexto = tolower(chartexto);
    //sendo que a letra a tem valor ascii = 97, se subtrairmos 97 de todos os caracteres, eles ficam ordenados de 0 até 25, o que facilita a criptografia
    chartexto = chartexto - 97;
    int charcrip = (chartexto + charchave) % 26; //definição matemática da cifra de vigenère
    charcrip = charcrip + 97; //soma-se 97 novamante para que o caractere volte a ser codificavel em ASCII
    if (eraMaiusculo)
        charcrip = toupper(charcrip);
    return charcrip;
}

char descriptografarCaractere(char chartexto,char charchave) {
    if (!isalpha(chartexto)) { //a função não irá descriptografar texto que não é alfabético
        return chartexto;
    }
    //a função para descriptografar irá processar todos os caracteres como se fossem minúsculos, para facilidade de código
    //por isso, é necessário guardar se o caractere no texto original era maiúsculo ou não
    int eraMaiusculo = 0;
    if (isupper(chartexto))
        eraMaiusculo = 1;
    chartexto = tolower(chartexto);
    //sendo que a letra a tem valor ascii = 97, se subtrairmos 97 de todos os caracteres, eles ficam ordenados de 0 até 25, o que facilita para descriptografar
    chartexto = chartexto - 97;
    int chardecrip = (chartexto - charchave + 26) % 26; //definição matemática da cifra de vigenère
    chardecrip = chardecrip + 97; //soma-se 97 novamante para que o caractere volte a ser codificavel em ASCII
    if (eraMaiusculo)
        chardecrip = toupper(chardecrip);
    return chardecrip;
}