#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "pecas.h"
#include "tela.h"

int globalCorPeca = 2; 

TipoPeca *AlocaPeca(){
	TipoPeca *novaPeca = malloc(sizeof(TipoPeca));
	
	return novaPeca;
}

void LiberaPeca(TipoPeca* peca){
	free(peca);
}

int GetTamanho(TipoPeca pecaTetris){
	int tamanho=0;
	
	while (VerificaSeBloco(pecaTetris.pecas[tamanho])) tamanho++; 
	return tamanho;
return tamanho;}


void GeraPeca(TipoPeca *ponteiroPeca){
	int tamanhoPeca,i;	// i= contador; x= host do tamanho da peça

	ponteiroPeca->x=10; //centraliza a peca
	ponteiroPeca->y=0;

	if(globalCorPeca>=6){
		globalCorPeca=2;
	}
	else{
		globalCorPeca++;
	}
;
	srand (time(NULL));
	tamanhoPeca= 3+rand()%3;
	ponteiroPeca->orient=rand()%2;
	
	for(i=0;i<tamanhoPeca;i++) // desenha blocos
	SetPeca(&(ponteiroPeca->pecas[i]),'0',globalCorPeca);

	for(i=tamanhoPeca;i<5;i++) //desenha espacos vazios
		SetPeca(&(ponteiroPeca->pecas[i]),'-',7);
}

void MovePecaX (TipoPeca *targetPeca, int inputX){
targetPeca->x=inputX;
}

void MovePecaY (TipoPeca *targetPeca, int inputY){
targetPeca->y=inputY;
}
