#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tela.h"
#include "engine.h"

int main () {
	char tela[15][25];
	int i,j;
	
	inicia_ncurses();

	criar_tela(tela);
	
	loop(tela);

	finaliza_ncurses();

	return 0;
}
