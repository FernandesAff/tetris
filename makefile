all: programa teste limpa

programa:main.o tela.o engine.o moduloauxengine.o peças.o
	gcc main.o tela.o engine.o moduloauxengine.o peças.o -o programa -lncurses

teste:teste.o tela.o engine.o moduloauxengine.o peças.o
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit teste.o tela.o engine.o moduloauxengine.o peças.o -lncurses -lcunit -o teste_gcov	

main.o: main.c tela.c tela.h engine.c engine.h peças.c peças.h moduloauxengine.c moduloauxengine.h
	gcc -c main.c 	

teste.o: teste.c tela.c engine.c moduloauxengine.c peças.c
	gcc -c teste.c

tela.o: tela.c tela.h
	gcc -c tela.c

peças.o: peças.h peças.c
	gcc -c peças.c

moduloauxengine.o: moduloauxengine.c moduloauxengine.h
	gcc -c moduloauxengine.c

engine.o: engine.c engine.h
	gcc -c engine.c	

limpa:
	rm *.o	
