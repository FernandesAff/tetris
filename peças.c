#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>

int main ()
{
	int x,i;	// i= contador; x= host do tamanho da peça
	char p[4];  //peça
	int t, sair=0, z=3, y=3;

	srand (time(NULL));
	x= rand()%6;
	if(x<=3){
		x=3;
	}
	for(i=0;i<x;i++){
		p[i]='o';
	}
	for(i=x;i<=5;i++){
		p[i]=' ';
	}
	initscr(); /* inicia ncurses */
	cbreak(); /* recebe input sem precisar apertar <enter> */
	noecho(); /* não mostra na tela input recebido */
	timeout(0); /* não fica esperando por input */
	curs_set(0); /* deixa o cursor invisivel*/
	while (sair == 0){
		switch(getch()){
			case KEY_LEFT: z--; break;
			case KEY_RIGHT: z++; break;
			case KEY_DOWN: y++; break;
			/* "asd" controlam o cursor */
			case 'q': sair = 1; break;
		}
		clear();
		mvaddstr(y, z, p);
		/* mostra char na posicao x, y */
	}
	endwin();
		printf("\n");
	
	return 0;
}