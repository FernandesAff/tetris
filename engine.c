#include <ncurses.h>
#include "tela.h"

int loop(char tela[][25]){

	int sair=0,x=0,y=0,prevx,prevy;
	cbreak();
	noecho();
	// incluir timeout() no futuro

while (sair==0){ //mudar para setas
	prevx=x;
	prevy=y;	

	switch(getch())
	{
		case 'a': x--; //limitar x caso em fronteira
			break;	
		case 's': y++;
			break;
		case 'd': x++;
			break;
		case 'w': y--;
			break;
		case 'q': sair=1;
			break;
	}
	
	tela[prevy][prevx]=' '; // apaga posicao antiga
	tela[y][x]='0'; //teste para o que seria a peca

	mostrar_tela(tela);
	}
//pega caractere
//opera sobre a peca
//desenha tela

return(0);

}
