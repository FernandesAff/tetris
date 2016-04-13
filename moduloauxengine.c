// modulo para testes nao rigorosos
#include "moduloauxengine.h"
#include <time.h>
#include <stdlib.h>

void insere(TipoTela *a){
	a->peca='0';
	a->cor=3;
}

void criaaleatorio(TipoTela tela[][25], int numlinhas, float probabilidade){
	int i,j;
	srand(time(NULL));
	for(i=14;i>=14-numlinhas;i--){
		for (j=0;j<24;j++){
			if (rand()%101<(probabilidade*100)) insere(&tela[i][j]);
			}
		}
}
