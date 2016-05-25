// modulo para testes nao rigorosos
#include "moduloauxengine.h"
#include <time.h>
#include <stdlib.h>

void Insere(TipoTela *a){
	a->peca='0';
	a->cor=3;
}

void CriaAleatorio(TipoTela tela[][25], int numLinhas, float probabilidade){
	int i,j;
	srand(time(NULL));
	for(i=14;i>=14-numLinhas;i--){
		for (j=0;j<25;j++){
			if (int (rand()%101<(probabilidade*100))) insere(&tela[i][j]);
			}
		}
}
