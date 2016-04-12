#define CORFUNDO 5
#define CORBLOCO 3
#define BLOCO '0'
#define VAZIO '-'
#include <ncurses.h>
#include "tela.h"


void inicia_ncurses(){
	initscr();
}

void finaliza_ncurses(){

	endwin();
}

int pega_input(){ //corrigir para as setas

	int input;
	switch(getch())
	{
		case KEY_LEFT: 
			input=1;
			break;	
		case KEY_DOWN:
			input=2;
			break;
		case KEY_RIGHT: 
			input=3;
			break;
		case KEY_UP: 
			input=4;
			break;
		case 'q':
			input=5;
			break;
	}

return input;
}


int posicaolivre(TipoTela pos){
	int livre=0;
	if (pos.peca != BLOCO) livre =1;
	return(livre);
}

void baixo(int *x, int *y, int *prevx, int *prevy, TipoTela tela[][25]){

if (posicaolivre(tela[(*y)+1][*x]) && *y<14) *y+=1;
else{
	tela[*y][*x].peca= BLOCO;
	tela[*y][*x].cor= CORBLOCO; //fixa peca
	*x=0;*prevx=1;*y=0,*prevy=1; //''cria'' nova peca
	}

}


int loop(TipoTela tela[][25]){

	int sair=0,x=0,y=0,prevx,prevy;

	inicia_ncurses();
	inicio_tela();
	cbreak();
	noecho();
	// incluir timeout() no futuro?
	keypad(stdscr, TRUE);
	tela[10][10].peca=BLOCO;
	tela[10][10].cor=CORBLOCO; // peca para teste de colisao


	int pontuacao = 0 ;// decidir o que fazer quanto a isso	

	while (sair==0){

		prevx=x;
		prevy=y;	
	
		mostrar_tela(tela, pontuacao); //desenha

		switch(pega_input()){
			case 1: 
				if (posicaolivre(tela[y][x-1]) && x>0)
				x--; //limitar x caso em fronteira
				break;	
			case 2:
				/*if (posicaolivre(tela[y+1][x]) && y<14)
				y++;
				else{
				tela[y][x]='0'; //fixa peca
				x=1;prevx=1;y=1,prevy=1; //''cria'' nova peca
				}*/
				baixo(&x,&y,&prevx,&prevy,tela);
				break;
			case 3: 
				if (posicaolivre(tela[y][x+1]) && x<24)
				x++;
				break;
			case 4: 
				if (posicaolivre(tela[y-1][x]) && y>0)
				y--; // eliminar esta opcao
				break;
			case 5: sair=1;
				break;
		}
	
		tela[prevy][prevx].peca=VAZIO;
		tela[prevy][prevx].cor=CORFUNDO; // apaga posicao antiga
		tela[y][x].peca=BLOCO;
		tela[y][x].cor=CORBLOCO; //teste para o que seria a peca
		clear();
	}
	fim_tela(pontuacao);
	finaliza_ncurses();
//pega caractere
//opera sobre a peca
//desenha tela

return(0);

}
