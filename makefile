all: programa teste limpa

programa: main.o tela.o ranking.o engine.o  pecas.o
	gcc main.o tela.o ranking.o engine.o pecas.o -o programa -lncurses

debug: ddebug limpa

ddebug: dmain.o tela.o ranking.o dengine.o  pecas.o pecas_inst.o
	gcc main.o tela.o ranking.o engine.o pecas.o pecas_inst.o -o dprograma -lncurses

teste:teste.o tela.o ranking.o engine.o pecas.o
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit teste.o tela.o ranking.o engine.o pecas.o -lncurses -lcunit -o teste_gcov	

main.o: main.c tela.c tela.h ranking.c ranking.h engine.c engine.h pecas.c pecas.h
	gcc -c main.c	

dmain.o: main.c tela.c tela.h ranking.c ranking.h engine.c engine.h pecas.c pecas.h pecas_inst.c pecas_inst.h
	gcc -c main.c

teste.o: teste.c tela.c ranking.c engine.c pecas.c
	gcc -ftest-coverage -fprofile-arcs -c teste.c

tela.o: tela.c tela.h
	gcc -c tela.c

ranking.o: ranking.c ranking.h
	gcc -c ranking.c	

pecas.o: pecas.h pecas.c 
	gcc -c pecas.c

pecas_inst.o: pecas_inst.h pecas_inst.c 
	gcc -c pecas_inst.c

engine.o: engine.c engine.h 
	gcc -c engine.c

dengine.o: engine.c engine.h 
	gcc -c engine.c -DDEBUG

limpa:
	rm *.o	

splint:
	splint *.c *.h 	-weak +compdef +infloops +sysdirerrors
