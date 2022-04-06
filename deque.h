#ifndef DEQUE_H

#define DEQUE_H
//estrutra do deque
typedef int type;
typedef struct {
    unsigned int head; //head aponta para a proxima posição vazia apos o primeiro elemento
    unsigned int tail; //tail aponta para o último elemento
    unsigned int imax;  //imax é o valor máximo do vetor
    type *vect;
} deque;

int startDeque (deque *d, unsigned int size); //inicia o deque com tamanho máximo igual ao parâmetro passado "size". retorna 0 se falhou
int emptyDeque (deque *d); //retorna 1 se o deque estiver vazio e 0 se não estiver
int fullDeque (deque *d); //retorna 1 se o deque estiver cheio e 0 se não estiver
void nextDeque (deque *d, unsigned int *index, int mode); //próxima posição. Método interno, não deve ser chamado pelo usuário
int addStartDeque (deque *d, type num); //insere um elemento "num" passado nos parâmetros no início do deque. retorna 1 se isso foi possivel
int addEndDeque (deque *d, type num); //insere um elemento "num" passado nos parâmetros no fim do deque. retorna 1 se isso foi possivel
int removeStartDeque (deque *d); //remove um elemento no início do deque. retorna 1 se isso foi possivel
int removeEndDeque (deque *d); //remove um elemento no final do deque. retorna 1 se isso foi possivel
type viewStartDeque (deque *d); //retorna um elemento no inicio do deque. Tem comportamento indefinido se o deque estiver vazio
type viewEndDeque (deque *d);  //retorna um elemento no final do deque. Tem comportamento indefinido se o deque estiver vazio
void wreckDeque (deque *d); //destrói o deque. 

#endif

