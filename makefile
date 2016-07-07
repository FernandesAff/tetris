all: programa limpao limpagcno

debug: ddebug teste limpao

programa: main.o tela.o ranking.o engine.o  pecas.o
	gcc -ftest-coverage -fprofile-arcs main.o tela.o ranking.o engine.o pecas.o -o programa -lncurses

ddebug: dmain.o tela.o ranking.o engine.o  pecas.o pecas_inst.o
	gcc -ftest-coverage -fprofile-arcs main.o tela.o ranking.o engine.o pecas.o pecas_inst.o -o dprograma -lncurses

teste:teste.o tela.o ranking.o engine.o pecas.o
	gcc -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit teste.o tela.o ranking.o engine.o pecas.o -lncurses -lcunit -o teste_gcov	

main.o: main.c tela.c tela.h ranking.c ranking.h engine.c engine.h pecas.c pecas.h
	gcc -ftest-coverage -fprofile-arcs -c main.c

dmain.o: main.c tela.c tela.h ranking.c ranking.h engine.c engine.h pecas.c pecas.h pecas_inst.c pecas_inst.h
	gcc -ftest-coverage -fprofile-arcs -c main.c		

teste.o: teste.c tela.c ranking.c engine.c pecas.c
	gcc -ftest-coverage -fprofile-arcs -c teste.c

tela.o: tela.c tela.h
	gcc -ftest-coverage -fprofile-arcs -c tela.c

ranking.o: ranking.c ranking.h
	gcc -ftest-coverage -fprofile-arcs -c ranking.c	

pecas.o: pecas.h pecas.c 
	gcc -ftest-coverage -fprofile-arcs -c pecas.c

pecas_inst.o: pecas_inst.h pecas_inst.c 
	gcc -ftest-coverage -fprofile-arcs -c pecas_inst.c

engine.o: engine.c engine.h 
	gcc -ftest-coverage -fprofile-arcs -c engine.c

limpao:
	rm *.o

limpagcno:
	rm *.gcno

splint:
	splint *.c *.h 	-weak +compdef +infloops +sysdirerrors
