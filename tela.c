#define BLOCO '0'
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tela.h"


void SetPecaCor(TipoTela* pecaDada, int corAferida){
	pecaDada->cor = corAferida;
}

void SetPecaCaractere(TipoTela* pecaDada,char caractereAferido){
	pecaDada->peca = caractereAferido;
};

void SetPeca(TipoTela *pecaDada, char caractereAferido, int corAferida){
	SetPecaCaractere(pecaDada,caractereAferido);
	SetPecaCor(pecaDada,corAferida);	
}

int VerificaSeBloco(TipoTela pecaDada){
	if (pecaDada.peca==BLOCO) return 1;
	else return 0;
}

void InicioTela(){
	int i,j;

	start_color(); 

	init_pair(1,COLOR_BLUE,COLOR_WHITE);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_GREEN,COLOR_WHITE);
	init_pair(4,COLOR_RED,COLOR_WHITE);
	init_pair(5,COLOR_CYAN,COLOR_WHITE);
	init_pair(6,COLOR_YELLOW,COLOR_WHITE);
	init_pair(7,COLOR_WHITE,COLOR_WHITE);
	init_pair(8,COLOR_RED,COLOR_BLACK);

	bkgd(COLOR_PAIR(8));

	move(1,13);
	printw("TETRIS");

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			mvaddch(i+3,j+3,'*'); 
		}
	}

	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 28, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 28, ACS_LRCORNER);
	mvhline(2, 3, ACS_HLINE, 25);
	mvhline(18, 3, ACS_HLINE, 25);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,28, ACS_VLINE, 15);

	move(19,3);
	printw("APERTE UMA TECLA PARA INICIAR");

	curs_set(0);
	getch();
	clear();

}

void CriarTela(TipoTela tela[][25]){
	int i,j;

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			tela[i][j].peca='-';
			tela[i][j].cor=7;
		}
	}	
}

void MostrarTela(TipoTela tela[][25], int pontos){
	int i,j;

	bkgd(COLOR_PAIR(1));

	move(1,3);
	printw("Pontuação:%d", pontos);
	mvaddch(8, 0, '=');
	mvaddch(8, 1, ACS_RARROW);
	mvaddch(8, 29, ACS_LARROW);
	mvaddch(8, 30, '=');
	
	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 28, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 28, ACS_LRCORNER);
	mvhline(2, 3, ACS_HLINE, 25);
	mvhline(18, 3, ACS_HLINE, 25);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,28, ACS_VLINE, 15);

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			attron(COLOR_PAIR(tela[i][j].cor));
			mvaddch(i+3,j+3, tela[i][j].peca); 
			attroff(COLOR_PAIR(tela[i][j].cor)); 
		}
	}
}

void FimTela(int pontos){
	int i, j;
	bkgd(COLOR_PAIR(8));

	move(1,3);
	printw("Pontuação:%d", pontos);

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			mvaddch(i+3,j+3,'*'); 
		}
	}

	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 28, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 28, ACS_LRCORNER);
	mvhline(2, 3, ACS_HLINE, 25);
	mvhline(18, 3, ACS_HLINE, 25);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,28, ACS_VLINE, 15);

	move(19,9);
	printw("FIM DE JOGO");

	getch();
	clear();

}
