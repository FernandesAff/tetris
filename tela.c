#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tela.h"

void inicio_tela(){
	int i,j;

	start_color(); 

	init_pair(1,COLOR_BLUE,COLOR_WHITE);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_GREEN,COLOR_WHITE);
	init_pair(4,COLOR_RED,COLOR_WHITE);
	init_pair(5,COLOR_WHITE,COLOR_WHITE);
	init_pair(6,COLOR_RED,COLOR_BLACK);

	bkgd(COLOR_PAIR(6));

	move(1,13);
	printw("TETRIS");

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			mvaddch(i+3,j+3,'*'); 
		}
	}

	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 30, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 30, ACS_LRCORNER);
	mvhline(2, 3, ACS_HLINE, 14);
	mvhline(18, 3, ACS_HLINE, 14);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,29, ACS_VLINE, 15);

	move(19,3);
	printw("APERTE UMA TECLA PARA INICIAR");

	curs_set(0);
	getch();
	clear();

}

void criar_tela(TipoTela tela[][25]){
	int i,j;

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			tela[i][j].peca='-';
			tela[i][j].cor=5;
		}
	}	
}

void mostrar_tela(TipoTela tela[][25], int pontos){
	int i,j;

	bkgd(COLOR_PAIR(1));

	move(1,3);
	printw("Pontuação:%d", pontos);
	mvaddch(7, 0, '=');
	mvaddch(7, 1, ACS_RARROW);
	mvaddch(7, 30, ACS_LARROW);
	mvaddch(7, 31, '=');
	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 30, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 30, ACS_LRCORNER);

	mvhline(2, 3, ACS_HLINE, 14);
	mvhline(18, 3, ACS_HLINE, 14);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,29, ACS_VLINE, 15);

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			attron(COLOR_PAIR(tela[i][j].cor));
			mvaddch(i+3,j+3, tela[i][j].peca); 
			attroff(COLOR_PAIR(tela[i][j].cor)); 
		}
	}
}

void fim_tela(int pontos){
	int i, j;
	bkgd(COLOR_PAIR(6));

	move(1,3);
	printw("Pontuação:%d", pontos);

	for(i=0;i<15;i++){
		for (j=0;j<25;j++){
			mvaddch(i+3,j+3,'*'); 
		}
	}

	mvaddch(2, 2, ACS_ULCORNER);
	mvaddch(2, 30, ACS_URCORNER);
	mvaddch(18, 2, ACS_LLCORNER);
	mvaddch(18, 30, ACS_LRCORNER);
	mvhline(2, 3, ACS_HLINE, 14);
	mvhline(18, 3, ACS_HLINE, 14);
	mvvline(3, 2, ACS_VLINE, 15);
	mvvline(3,29, ACS_VLINE, 15);

	move(19,3);
	printw("FIM DE JOGO");

	getch();
	clear();

}