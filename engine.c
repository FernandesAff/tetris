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
		case 'a': 
			input=1;
			break;	
		case 's':
			input=2;
			break;
		case 'd': 
			input=3;
			break;
		case 'w': 
			input=4;
			break;
		case 'q':
			input=5;
			break;
	}

return input;
}


int posicaolivre(char pos){
	int livre=0;
	if (pos==' ') livre =1;
	return(livre);
}

void baixo(int *x, int *y, int *prevx, int *prevy, char tela[][25]){

if (posicaolivre(tela[(*y)+1][*x]) && *y<14)
*y+=1;
else{
	tela[*y][*x]='0'; //fixa peca
	*x=1;*prevx=1;*y=1,*prevy=1; //''cria'' nova peca
	}

}


int loop(char tela[][25]){

	int sair=0,x=1,y=1,prevx,prevy;
	cbreak();
	noecho();
	// incluir timeout() no futuro?

	tela[10][10]='0'; // peca para teste de colisao

	

while (sair==0){
	prevx=x;
	prevy=y;	
	
	mostrar_tela(tela); //desenha

	switch(pega_input())
	{
		case 1: 
			if (posicaolivre(tela[y][x-1]) && x>1)
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
	
	tela[prevy][prevx]=' '; // apaga posicao antiga
	tela[y][x]='0'; //teste para o que seria a peca
	}
//pega caractere
//opera sobre a peca
//desenha tela

return(0);

}
