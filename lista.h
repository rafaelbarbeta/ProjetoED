#ifndef LISTA_H

#define LISTA_H

typedef int type;
typedef struct {
    struct node *sentinel;
    unsigned int qty;
} listaEnc;

struct node {
    struct node *next, *prev;
    type data;
};

void startList (listaEnc *l); //inicia
int emptyList (listaEnc *l); //vazio
void addStartList (listaEnc *l, type num); //inseri (inicio)
void addEndList (listaEnc *l, type num); //inseri (final)
void removeStartList (listaEnc *l); //remove (inicio)
void removeEndList (listaEnc *l); //remove (final)
unsigned int sizeList (listaEnc *l); //tamanho
type viewStartList (listaEnc *l); //visualizar (inicio)
type viewEndList (listaEnc *l); //visualizar (final)
void wreckList (listaEnc *l); //destroi

#endif 