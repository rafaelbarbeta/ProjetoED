#ifndef DEQUE_H

#define DEQUE_H
//estrutra do deque
typedef int type;
typedef struct {
    unsigned int head; //head aponta para a proxima posicao vazia apos o primeiro elemento
    unsigned int tail; //tail aponta para o ultimo elemento
    unsigned int imax;  //imax eh o valor maximo do vetor
    type *vect;
} deque;

int startDeque (deque *d, unsigned int size); //inicia o deque com tamanho maximo igual ao parametro passado "size". retorna 0 se falhou
int emptyDeque (deque *d); //retorna 1 se o deque estiver vazio e 0 se nao estiver
int fullDeque (deque *d); //retorna 1 se o deque estiver cheio e 0 se nao estiver
void nextDeque (deque *d, unsigned int *index, int mode); //proxima posicao. Funcao interna, não deve ser chamado pelo usuário
int addStartDeque (deque *d, type num); //insere um elemento "num" passado nos parametros no inicio do deque. retorna 1 se isso foi possivel
int addEndDeque (deque *d, type num); //insere um elemento "num" passado nos parametros no fim do deque. retorna 1 se isso foi possivel
int removeStartDeque (deque *d); //remove um elemento no inicio do deque. retorna 1 se isso foi possivel
int removeEndDeque (deque *d); //remove um elemento no final do deque. retorna 1 se isso foi possivel
type viewStartDeque (deque *d); //retorna o elemento do inicio do deque. Para o usuario garantir o retorno correto, o deque deve ter ao menos um elemento, ou seja, tem comportamento indefinido se o deque estiver vazio 
type viewEndDeque (deque *d);  //retorna o elemento do final do deque. Para o usuario garantir o retorno correto, o deque deve ter ao menos um elemento, ou seja, tem comportamento indefinido se o deque estiver vazio 
void wreckDeque (deque *d); //destroi o deque. 

#endif

