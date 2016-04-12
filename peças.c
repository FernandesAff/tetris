#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>

void gera_peca (TipoTela *p){
	int z,y,i;	// i= contador; x= host do tamanho da peça

	srand (time(NULL));
	z= rand()%6;
	y=2+rand()%3;
	if(z<=3){
		z=3;
	}
	for(i=0;i<z;i++){
		p[i].peca='o';
		p[i].cor=y;
	}
	for(i=z;i<=5;i++){
		p[i].peca='-';
		p[i].cor=5;
	}

	return;
}

int main ()
{
	int t, sair=0, x=3, y=3;
	char str[4];
	
	gera_peca(str);
	initscr(); /* inicia ncurses */
	cbreak(); /* recebe input sem precisar apertar <enter> */
	noecho(); /* não mostra na tela input recebido */
	timeout(0); /* não fica esperando por input */
	curs_set(0); /* deixa o cursor invisivel*/
	keypad(stdscr, TRUE);
	while (sair == 0){
		switch(getch()){
			case KEY_LEFT: x--; break;
			case KEY_RIGHT: x++; break;
			case KEY_DOWN: y++; break;
			/* "asd" controlam o cursor */
			case 'q': sair = 1; break;
		}
		clear();
		
		mvaddstr(y, x, str);
		/* mostra char na posicao x, y */
	}
	endwin();
		printf("\n");
	
	return 0;
}