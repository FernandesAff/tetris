all: programa teste limpa

programa:main.o tela.o engine.o  pecas.o
	gcc main.o tela.o engine.o pecas.o -o programa -lncurses

teste:teste.o tela.o engine.o pecas.o
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit teste.o tela.o engine.o pecas.o -lncurses -lcunit -o teste_gcov	

main.o: main.c tela.c tela.h engine.c engine.h pecas.c pecas.h
	gcc -c main.c 	

teste.o: teste.c tela.c engine.c pecas.c
	gcc -c teste.c

tela.o: tela.c tela.h
	gcc -c tela.c

pecas.o: pecas.h pecas.c
	gcc -c pecas.c

engine.o: engine.c engine.h
	gcc -c engine.c	

limpa:
	rm *.o	

splint:
	splint *.c *.h -weak -redef +infloops +compdef +sysdirerrors

