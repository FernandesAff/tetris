#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "peças.h"
#include "tela.h"

int get_tamanho(TipoPeca pecatetris){
	int tamanho=0;
	
	while (verifica_se_bloco(pecatetris.pecas[tamanho])) tamanho++; 
	return tamanho;
return tamanho;}


void gera_peca(TipoPeca *ponteiropeca, int *corpeca){
	int tamanhopeca,i;	// i= contador; x= host do tamanho da peça

	ponteiropeca->x=10; //centraliza a peca
	ponteiropeca->y=0;

	if(*corpeca>=6){
		*corpeca=2;
	}
	else{
		*corpeca=*corpeca+1;
	}

	srand (time(NULL));
	tamanhopeca= 3+rand()%3;
	ponteiropeca->orient=rand()%2;
	
	for(i=0;i<tamanhopeca;i++) // desenha blocos
		set_peca(&(ponteiropeca->pecas[i]),'0',*corpeca);

	for(i=tamanhopeca;i<5;i++) //desenha espacos vazios
		set_peca(&(ponteiropeca->pecas[i]),'-',7);
	

}

void move_peca_x (TipoPeca *targetpeca, int inputx){
targetpeca->x=inputx;
}

void move_peca_y (TipoPeca *targetpeca, int inputy){
targetpeca->y=inputy;
}
