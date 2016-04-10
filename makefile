all: programa limpa

programa:main.o tela.o
	gcc main.o tela.o -o programa -lncurses

main.o: main.c tela.c tela.h
	gcc -c main.c 	

tela.o: tela.c tela.h
	gcc -c tela.c

limpa:
	rm *.o	