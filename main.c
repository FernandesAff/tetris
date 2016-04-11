#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tela.h"
#include "engine.h"

int main () {
	char tela[15][25];
	int i,j;
	
	initscr();

	criar_tela(tela);
	
	loop(tela);

	endwin();

	return 0;
}
