#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "pecas.h"
#include "tela.h"
#define TAMANHO_X 5
#define TAMANHO_Y 5
#define COR_FUNDO 7
#define B '0'
#define V '-'
#define NUM_PECAS 7



struct TipoPeca{
	TipoTela pecas[TAMANHO_Y][TAMANHO_X];
	int x;
	int y;
	int orient;
};


static int globalCorPeca = 2; 


static char MATRIZ_DE_PECAS [NUM_PECAS][TAMANHO_Y][TAMANHO_X] =  
{
	{
	 {B,B,B,B,B},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},
	{
	 {B,B,B,B,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},
	{
	 {B,B,B,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},
	{
	 {B,B,V,V,V},
	 {V,B,V,V,V},
	 {V,B,B,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},
	{
	 {B,B,B,B,B},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},{
	 {B,V,V,V,V},
	 {B,V,V,V,V},
	 {B,B,B,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}	
	},{
	 {B,B,V,V,V},
	 {B,B,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	}
};


void CopiaDaMatrizDePecas(char MatrizFonte[][5], TipoTela MatrizAlvo[][5]){
	int i,j;
	TipoTela bloquete,
		 vazio;

	if(globalCorPeca>=6){
		globalCorPeca=2;
	}
	else{
		globalCorPeca++;
	}


	bloquete.peca = B;
	bloquete.cor = globalCorPeca;
	vazio.peca = V;
	vazio.cor = COR_FUNDO;


	for (i=0;i<5;i++){
		for (j=0; j<5; j++){

			if (MatrizFonte[i][j]==B){
				MatrizAlvo[i][j] = bloquete;
				}
			else{
				MatrizAlvo[i][j] = vazio;
				}
			}
		}
	}


void GeraPeca(TipoPeca *ponteiroPeca){

	int indicePeca=-1;

	srand (time(NULL));	
	indicePeca = rand() % NUM_PECAS;
	ponteiroPeca-> x=10; //centraliza a peca
	ponteiroPeca-> y=0;
	ponteiroPeca-> orient = 0;
	
	CopiaDaMatrizDePecas(MATRIZ_DE_PECAS[indicePeca],ponteiroPeca->pecas);


}


TipoTela PecaGetBloco(TipoPeca *peca, int y, int x){
	return peca->pecas[y][x];
}

int PecaGetCor(TipoPeca *peca){
	int cor=0,
	    i=0,
	    j=0,
	    quit=0;

	for (i=0; i<TAMANHO_X && !quit; i++) {
		for(j=0; j<TAMANHO_Y && !quit; j++){	
			if (peca->pecas[i][j].cor != COR_FUNDO) {
				cor= peca->pecas[i][j].cor;
				quit=1;
				}
			}
		}
	return cor;
	}

void CopiaPeca(TipoPeca *pecaIn, TipoPeca *pecaOut){
	int i=0, j=0;
	pecaOut->x=pecaIn->x;
	pecaOut->y=pecaIn->y;
	pecaOut->orient=pecaIn->orient;
	for (i=0;i<TAMANHO_Y;i++) 
		for (j=0;j<TAMANHO_X;j++) pecaOut->pecas[i][j]=pecaIn->pecas[i][j];
	}

int PecaGetX(TipoPeca *peca){
	return peca->x;
	}

int PecaGetY(TipoPeca *peca){
	return peca->y;
	}

int PecaGetOrient(TipoPeca *peca){
	return peca->orient;
	}

TipoPeca *AlocaPeca(){
	TipoPeca *novaPeca = malloc(sizeof(TipoPeca));
	
	return novaPeca;
	}

void LiberaPeca(TipoPeca* peca){
	free(peca);
	}

int PecaGetTamanhoX(TipoPeca *peca){
	int tamanho=0,
	    tamanhoMax=0,
	    i,
	    j;

	for (i=0; i<TAMANHO_Y; i++){
		for (j=0; j<TAMANHO_X; j++){
			if( VerificaSeBloco(PecaGetBloco(peca,i,j)) )
				tamanho=j;
			}
		if (tamanho>tamanhoMax) tamanhoMax=tamanho;
		if (tamanho == TAMANHO_X) break;  
		}

	return tamanhoMax;
	}

int PecaGetTamanhoY(TipoPeca *peca){
	int tamanho=0,
	    tamanhoMax=0,
	    i,
	    j;

	for (j=0; j<TAMANHO_X; j++){
		for (i=0; i<TAMANHO_Y; i++){
			if( VerificaSeBloco(PecaGetBloco(peca,i,j)) )
				tamanho=i;
			}
		if (tamanho>tamanhoMax) tamanhoMax=tamanho;
		if (tamanho == TAMANHO_X) break;  
		}

	return tamanhoMax;
	}


void MovePecaX (TipoPeca *targetPeca, int inputX){
	targetPeca->x=inputX;
	}

void MovePecaY (TipoPeca *targetPeca, int inputY){
	targetPeca->y=inputY;
	}
