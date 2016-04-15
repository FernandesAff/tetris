#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "peças.h"

void gera_peca(TipoPeca *ponteiropeca, int *corpeca){
	int tamanhopeca,i;	// i= contador; x= host do tamanho da peça

	ponteiropeca->x=10; //centraliza a peca
	ponteiropeca->y=0;

	if(*corpeca>=6){
		*corpeca=2;
	}
	else{
		*corpeca=*corpeca+1;
	}

	srand (time(NULL));
	tamanhopeca= 3+rand()%3;
	ponteiropeca->orient=rand()%2;
	
	for(i=0;i<tamanhopeca;i++){ // desenha blocos
		ponteiropeca->pecas[i].peca='0';
		ponteiropeca->pecas[i].cor=*corpeca;
	}
	for(i=tamanhopeca;i<5;i++){ //desenha espacos vazios
		ponteiropeca->pecas[i].peca='-';
		ponteiropeca->pecas[i].cor=7;
	}

}

void move_peca_x (TipoPeca *targetpeca, int inputx){
targetpeca->x=inputx;
}

void move_peca_y (TipoPeca *targetpeca, int inputy){
targetpeca->y=inputy;
}


/*
int main ()
{
	int t, sair=0, x=3, y=3;
	char str[4];
	
	gera_peca(str);
	initscr(); // inicia ncurses 
	cbreak(); // recebe input sem precisar apertar <enter> 
	noecho(); // não mostra na tela input recebido 
	timeout(0); // não fica esperando por input 
	curs_set(0); // deixa o cursor invisivel
	keypad(stdscr, TRUE);
	while (sair == 0){
		switch(getch()){
			case KEY_LEFT: x--; break;
			case KEY_RIGHT: x++; break;
			case KEY_DOWN: y++; break;
			// "asd" controlam o cursor 
			case 'q': sair = 1; break;
		}
		clear();
		
		mvaddstr(y, x, str);
		// mostra char na posicao x, y
	}
	endwin();
		printf("\n");
	
	return 0;
} */
