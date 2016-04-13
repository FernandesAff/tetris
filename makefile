all: programa limpa

programa:main.o tela.o engine.o moduloauxengine.o peças.o
	gcc main.o tela.o engine.o moduloauxengine.o peças.o -o programa -lncurses

main.o: main.c tela.c tela.h engine.c engine.h peças.c peças.h moduloauxengine.c moduloauxengine.h
	gcc -c main.c 	

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
