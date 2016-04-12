#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tela.h"
#include "engine.h"

int main () {
	TipoTela tela[15][25];
	int i,j;
	
	criar_tela(tela);
	
	loop(tela);

	return 0;
}
