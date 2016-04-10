#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include "tela.h"

int main () {
	char tela[15][25];
	int i,j;
	
	initscr();

	criar_tela(tela);
	mostrar_tela(tela);	

	getch();
	endwin();

	return 0;
}