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

void startDeque (deque *d, unsigned int size); //inicia o deque com tamanho maximo igual ao parametro passado "size"
int emptyDeque (deque *d); //retorna 1 se o deque estiver vazio e 0 se nao estiver
int fullDeque (deque *d); //retorna 1 se o deque estiver cheio e 0 se nao estiver
void nextDeque (deque *d, unsigned int *index, int mode); //proxima posicao. Metodo interno, nao deve ser chamado pelo usuario
int addStartDeque (deque *d, type num); //insere um elemento "num" passado nos parametros no inicio do deque. retorna 1 se isso foi possivel
int addEndDeque (deque *d, type num); //insere um elemento "num" passado nos parametros no fim do deque. retorna 1 se issp foi possivel
int removeStartDeque (deque *d); //remove um elemento no inicio do deque. retorna 1 se isso foi possivel
int removeEndDeque (deque *d); //remove um elemento no final do deque. retorna 1 se isso foi possivel
type viewStartDeque (deque *d); //retorna um elemento no inicio do deque. Tem comportamento indefinido se o deque estiver vazio
type viewEndDeque (deque *d);  //retorna um elemento no final do deque. Tem comportamento indefinido se o deque estiver vazio
void wreckDeque (deque *d); //destroi o deque. 

#endif

