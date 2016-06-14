///	Gerencia a criação e manipulação da tela.
/// Este módulo implementa a tela do jogo, bem
/// como gerencia as operações relacionadas a ela.
///	
/// \file tela.c
///	\author André
/// \since 11/04/16
/// \version 2.3

#define BLOCO '0'
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "tela.h"
#include "ranking.h"

///	Função que muda a cor de uma peça.
///
///	\param *pecaDada ponteiro para peça.
/// \param corAferida inteiro referente à cor.

void SetPecaCor(TipoTela* pecaDada, int corAferida){
	pecaDada->cor = corAferida;
}

///	Função que indica o caractere a ser usado em uma peça
///
///	\param *pecaDada ponteiro para peça.
/// \param caractereAferido caractere a ser passado para a peça.

void SetPecaCaractere(TipoTela* pecaDada,char caractereAferido){
	pecaDada->peca = caractereAferido;
};

///	Função que faz as alterações em uma peça.
///
///	\param *pecaDada ponteiro para peça.
/// \param caractereAferido  caractere a ser passado para a peça.
/// \param corAferida inteiro referente à cor.

void SetPeca(TipoTela *pecaDada, char caractereAferido, int corAferida){
	SetPecaCaractere(pecaDada,caractereAferido);
	SetPecaCor(pecaDada,corAferida);	
}

///	Função que verifica se uma peça tem o símbolo do fundo.
///
///	\param *pecaDada ponteiro para peça.
/// \return 0 ou 1.

int VerificaSeBloco(TipoTela pecaDada){
	if (pecaDada.peca==BLOCO) return 1;
	else return 0;
}

///	Função que gera e mostra a tela de início.

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
			mvaddch(i+3,j+3,(chtype)'*'); 
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
}

///	Função que cria a tela vazia.
///
///	\param tela[][25] matriz da tela.

void CriarTela(TipoTela tela[][25]){
	int i,j;

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			tela[i][j].peca='-';
			tela[i][j].cor=7;
		}
	}	
}

void MostrarTela(TipoTela tela[][25], int pontos, int tempoDecorrido){
	int i,j;

	bkgd(COLOR_PAIR(1));

	move(1,3);
	printw("Pontuação:%d", pontos);
	move(1,20);
	printw("Tempo:%d",tempoDecorrido);
	mvaddch(8, 0, (chtype)'=');
	mvaddch(8, 1, ACS_RARROW);
	mvaddch(8, 29, ACS_LARROW);
	mvaddch(8, 30, (chtype)'=');
	
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
			mvaddch(i+3,j+3, (chtype)tela[i][j].peca); 
			attroff(COLOR_PAIR(tela[i][j].cor)); 
		}
	}
}

void FimTela(int pontos){
	int i;
	FILE *fp;
	TipoJogador jogador;

	fp=fopen(ARQUIVO, "r");
	bkgd(COLOR_PAIR(8));

	move(1,3);
	printw("Pontuação:%d", pontos);

	mvaddch(2, 2, ACS_ULCORNER);
	mvhline(2, 3, ACS_HLINE, 29);
	mvaddch(2, 32, ACS_URCORNER);
	
	mvvline(3, 2, ACS_VLINE, 1);
	mvvline(3,32, ACS_VLINE, 1);
	move(3,14);
	printw("RANKING");
	mvaddch(4, 2, ACS_LTEE);
	mvhline(4, 3, ACS_HLINE, 29);
	mvaddch(4, 32, ACS_RTEE);

	mvvline(5, 2, ACS_VLINE, 1);
	mvvline(5,32, ACS_VLINE, 1);
	move(5,3);
	printw("APELIDO PONTOS DATA     TEMPO");
	mvaddch(6, 2, ACS_LTEE);
	mvhline(6, 3, ACS_HLINE, 29);
	mvaddch(6, 32, ACS_RTEE);
	
	for(i=0;i<10;i+=2){
		mvvline(7+i, 2, ACS_VLINE, 1);
		mvvline(7+i,32, ACS_VLINE, 1);
		if(fscanf(fp,"%s %d %d/%d/%d %d\n", jogador.apelido, &jogador.pontos, &jogador.dia, &jogador.mes, &jogador.ano, &jogador.tempo)!=EOF){
			mvaddstr(7+i, 3, jogador.apelido);
			move(7+i,11);
			printw("%d",jogador.pontos);
			move(7+i,18);
			printw("%d/%d/%d",jogador.dia, jogador.mes, jogador.ano-2000);
			move(7+i,27);
			printw("%d",jogador.tempo);
		}	
		mvaddch(8+i, 2, ACS_LTEE);
		mvhline(8+i, 3, ACS_HLINE, 29);
		mvaddch(8+i, 32, ACS_RTEE);
	}	

	mvvline(17, 2, ACS_VLINE, 1);
	mvvline(17,32, ACS_VLINE, 1);
	move(17,12);
	printw("FIM DE JOGO");
	mvaddch(18, 2, ACS_LLCORNER);
	mvhline(18, 3, ACS_HLINE, 29);
	mvaddch(18, 32, ACS_LRCORNER);

	fclose(fp);
	getch();
	clear();
}
