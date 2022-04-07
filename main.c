#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "deque.h"

char criptografarCaractere(char chartexto,char charchave);
char descriptografarCaractere(char chartexto,char charchave);

int main () {
    printf("\t\t\tCifra De Vigenère : Versão Terminal\n");
    printf("Selecione uma opção:\n");
    printf("C : Criptografar texto\n");
    printf("D : Descriptografar texto\n");
    printf("E : Sair do programa\n");
    char option = 0;
    do {
        scanf(" %c",&option);
        switch(option) {
            case 'C' : {
                //uma ideia bacana é transformar essa inicialização em uma função (vai ser utilizada para descriptografar tbm)
                char proxLetra = 0;
                listaEnc textoPuro;
                deque chave; 
                startList(&textoPuro);
                startDeque(&chave,100);
                printf("Por favor digite um texto para CRIPTOGRAFAR:\n");
                while (proxLetra != '\n') {
                    scanf(" %c",&proxLetra);
                    addEndList(&textoPuro,proxLetra);
                }
                removeEndList(&textoPuro);
                proxLetra = 0;
                printf("Insira uma chave contendo apenas letras (máximo de 100):\n");
                while (proxLetra != '\n') {
                    scanf(" %c",&proxLetra);
                    addEndDeque(&chave,proxLetra);
                }
                removeEndDeque(&chave);
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
                }
            }
            break;
            case 'D' : break;
            case 'E' : return 0;
            default : printf("Opção Inválida!\n"); option = 0; break;
        }
    } while (!option);
}