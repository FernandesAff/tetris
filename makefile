all: programa limpa

programa:main.o tela.o engine.o
	gcc main.o tela.o engine.o -o programa -lncurses

main.o: main.c tela.c tela.h engine.c engine.h
	gcc -c main.c 	

tela.o: tela.c tela.h
	gcc -c tela.c

engine.o: engine.c engine.h
	gcc -c engine.c

limpa:
	rm *.o	
