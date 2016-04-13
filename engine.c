#define TAMANHOTELAY 15
#define TAMANHOTELAX 25
#define CORFUNDO 5
#define CORBLOCO 3
#define BLOCO '0'
#define VAZIO '-'
#include <ncurses.h>
#include "tela.h"
#include "moduloauxengine.h"

void deletabloco(TipoTela *unidade){
	unidade->cor=CORFUNDO;
	unidade->peca=VAZIO;
}

void inserebloco(TipoTela *unidade){
	unidade->cor=CORBLOCO;
	unidade->peca=BLOCO;	
}

int verificalinhas(TipoTela tela[][TAMANHOTELAX]){//verifica se ha alguma linha completa
	int i,j, completa=1;	  //se houver, retorna a posicao y dela
	for(i=TAMANHOTELAY-1;i>=0;i--){
		for (j=0;j<TAMANHOTELAX-1;j++){
			if (tela[i][j].peca==VAZIO) {
				completa=0;
				j=100;
				}
			}
		if (completa==1) return i;
		completa=1;
		}
	return(-1); //caso nenhuma linha esteja completa, retorna -1
}

void deletalinhas(TipoTela tela[][TAMANHOTELAX]){ 
	int linha=0, i;
	while (linha!=-1){
		linha=verificalinhas(tela);
		if (linha!=-1) 
			for (i=0;i<TAMANHOTELAX;i++) deletabloco(&tela[linha][i]);
	}
}


void fixa_e_cria_nova_peca(int *x,int *y,int *prevx,int *prevy,TipoTela tela[][TAMANHOTELAX]){ //e deleta linhas se completas
	tela[*y][*x].peca= BLOCO;
	tela[*y][*x].cor= CORBLOCO; //fixa peca
	*x=0;*prevx=1;*y=0,*prevy=1; //''cria'' nova peca
	deletalinhas(tela);
}


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

void baixo(int *x, int *y, int *prevx, int *prevy, TipoTela tela[][TAMANHOTELAX]){


if (posicaolivre(tela[(*y)+1][*x]) )*y+=1; 
else fixa_e_cria_nova_peca(x,y,prevx,prevy,tela);

if (*y>=TAMANHOTELAY-1) {
	deletabloco(&tela[*prevy][*prevx]);
	fixa_e_cria_nova_peca(x,y,prevx,prevy,tela);
}




/*if (posicaolivre(tela[(*y)+1][*x]) && *y<TAMANHOTELAY-1) *y+=1;
else{	
	tela[*y][*x].peca= BLOCO;
	tela[*y][*x].cor= CORBLOCO; //fixa peca
	*x=0;*prevx=1;*y=0,*prevy=1; //''cria'' nova peca
	}
*/
}


int loop(TipoTela tela[][TAMANHOTELAX]){

	criaaleatorio(tela, 3, 0.87);

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
				baixo(&x,&y,&prevx,&prevy,tela);
				break;
			case 3: 
				if (posicaolivre(tela[y][x+1]) && x<TAMANHOTELAX-1)
				x++;
				break;
			case 4: 
				if (posicaolivre(tela[y-1][x]) && y>0)
				y--; // eliminar esta opcao
				break;
			case 5: sair=1;
				break;
		}
		deletabloco(&tela[prevy][prevx]); // apaga posicao antiga
		inserebloco(&tela[y][x]); // <- teste para o que seria a peca
		clear();
	}
	fim_tela(pontuacao);
	finaliza_ncurses();

return(0);

}
