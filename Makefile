all:gtkVigenere vigenere testes

gtkVigenere: gtkvigenere.c
	gcc -o gtkvigenere gtkvigenere.c deque.c deque.h lista.c lista.h `pkg-config --cflags --libs gtk+-3.0`

vigenere: main.c
	gcc -o vigenere main.c lista.h lista.c deque.h deque.c `pkg-config --cflags --libs gtk+-3.0`

testes: testeEstruturas.c
	gcc -o testes testeEstruturas.c lista.h lista.c deque.h deque.c listaordenada.h listaordenada.c `pkg-config --cflags --libs check`