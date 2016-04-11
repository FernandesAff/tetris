#include <ncurses.h>
#include "tela.h"


int posicaolivre(char pos){
	int livre=0;
	if (pos==' ') livre =1;
	return(livre);
}

int loop(char tela[][25]){

	int sair=0,x=1,y=1,prevx,prevy;
	cbreak();
	noecho();
	// incluir timeout() no futuro

	tela[10][10]='0'; // peca para teste de colisao

	

while (sair==0){ //mudar para setas
	prevx=x;
	prevy=y;	
	
	mostrar_tela(tela); //desenha

	switch(getch())
	{
		case 'a': 
			if (posicaolivre(tela[y][x-1]) && x>1)
			x--; //limitar x caso em fronteira
			break;	
		case 's':
			if (posicaolivre(tela[y+1][x]) && y<14)
			y++;
			else{
			tela[y][x]='0'; //fixa peca
			x=1;prevx=1;y=1,prevy=1; //''cria'' nova peca
			}
			break;
		case 'd': 
			if (posicaolivre(tela[y][x+1]) && x<24)
			x++;
			break;
		case 'w': 
			if (posicaolivre(tela[y-1][x]) && y>0)
			y--; // eliminar esta opcao
			break;
		case 'q': sair=1;
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
