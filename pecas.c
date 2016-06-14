///	Gerencia a criação e manipulação de peças no jogo. 
///	Este módulo implementa as peças do jogo, bem como
/// todas as operações relacionadas à elas.
///	
/// \file pecas.c
///	\author Anderson
/// \since 11/04/16
/// \version 2.6

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <ncurses.h>
#include "pecas.h"
#include "tela.h"
#define TAMANHO_X 5
#define TAMANHO_Y 5
#define COR_FUNDO 7
#define B '0'
#define V '-'
#define NUM_PECAS 8

static int globalCorPeca = 2; 

static char MATRIZ_DE_PECAS [NUM_PECAS][TAMANHO_Y][TAMANHO_X] =  {
	{
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V}
	},
	{
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,V,V,V}
	},
	{
	 {V,V,V,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,V,V,V}
	},
	{
	 {V,V,V,V,V},
	 {V,B,B,V,V},
	 {V,V,B,V,V},
	 {V,V,B,B,V},
	 {V,V,V,V,V}
	},
	{
	 {V,V,V,V,V},
	 {B,B,B,B,B},
	 {V,V,B,V,V},
	 {V,V,B,V,V},
	 {V,V,V,V,V}
	},{
	 {V,V,V,V,V},
	 {V,B,V,V,V},
	 {V,B,V,V,V},
	 {V,B,B,B,V},
	 {V,V,V,V,V}	
	},{
	 {V,V,V,V,V},
	 {V,B,B,V,V},
	 {V,B,B,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	},{
	 {V,V,V,V,V}, //peca vazia
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V},
	 {V,V,V,V,V}
	}
};

///	Função que incrementa a velocidade de queda da peça.
///
///	\param *peça ponteiro para a peça atual.
/// \param multiplicador inteiro que representa o quanto a velocidade
/// de queda da peça será incrementada.

void SpeedUp(TipoPeca *peca, int multiplicador){
	if (peca->speed < 50) 	
		peca-> speed *= multiplicador; 
}

///	Função que rotaciona a peça.
///
///	\param *peça ponteiro para a peça atual.

void RotacionaPeca(TipoPeca *peca){
	
	int i,
	    j;
	TipoPeca *pecaAux;
	pecaAux = AlocaPeca();

	*pecaAux = *peca;

	for (i=0;i<5;i++){
		for(j=0;j<5;j++){
			// (x,y) -> (y,6-x) rotacao em 90 graus, horario
			peca->pecas[i][j] = pecaAux->pecas[j][4-i]; 
		}		
	}
	LiberaPeca(pecaAux);
}

///	Função que copia uma peça de uma matriz à outra.
///
///	\param MatrizFonte[][5] matriz que contém a peça de origem.
/// \param MatrizAlvo[][5] mattriz que receberá a peça.

void CopiaDaMatrizDePecas(char MatrizFonte[][5], TipoTela MatrizAlvo[][5]){
	int i,
		j;
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

///	Função que gera uma peça aleatoriamente.
/// 
/// \param *ponteiropeça ponteiro para uma peça.

void GeraPeca(TipoPeca *ponteiroPeca){

	int indicePeca = -1,
	    direcao = -1;

	srand ((unsigned int)time(NULL));	
	indicePeca = rand() % (NUM_PECAS - 1); //sendo a ultima peca a peca vazia
	srand ((unsigned int)time(NULL));	
	direcao = rand() % 4;

	ponteiroPeca-> x=10; //centraliza a peca
	ponteiroPeca-> y=0;
	ponteiroPeca-> speed = 1;
	
	CopiaDaMatrizDePecas(MATRIZ_DE_PECAS[indicePeca],ponteiroPeca->pecas);

	switch (direcao){
		case(0): //nao rotaciona
			break;
		case(1):// rotaciona 1x
			RotacionaPeca(ponteiroPeca);
			break;
		case(2):// rotaciona 2x  ...
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			break;
		case(3):
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			break;
	}
}

///	Função que gera uma peça específica.
/// Gera uma peça não linear, que varia entre modelos específicos
/// do jogo.
///
///	\param *ponteiroPeca ponteiro para uma peça.
/// \param indicePeca inteiro que indica qual peça específica deve ser
/// gerada.
/// \param direcao inteiro que define a direção da peça a ser gerada.

void GeraPecaEspecifica(TipoPeca *ponteiroPeca, int indicePeca, int direcao){

	ponteiroPeca-> x=10; //centraliza a peca
	ponteiroPeca-> y=0;
	ponteiroPeca-> speed = 1;
	
	CopiaDaMatrizDePecas(MATRIZ_DE_PECAS[indicePeca],ponteiroPeca->pecas);

	switch (direcao){
		case(0): //nao rotaciona
			break;
		case(1):// rotaciona 1x
			RotacionaPeca(ponteiroPeca);
			break;
		case(2):// rotaciona 2x  ...
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			break;
		case(3):
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			RotacionaPeca(ponteiroPeca);
			break;
		}
}

///	Função que retorna uma peça e sua posição.
///
///	\param *peça ponteiro para peça.
/// \param y inteiro que indica a posição horizontal da peça.
/// \param x inteiro que indica a posição vertical da peça.
/// \return a matriz da peça.

TipoTela PecaGetBloco(TipoPeca *peca, int y, int x){
	return peca->pecas[y][x];
}

///	Função que retorna a cor de uma peça.
///
///	\param *peca ponteiro para peça.
/// \return um inteiro que indica a cor da peça.

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

///	Função que copia uma peça.
///
///	\param *pecaIn peça que será copiada;
/// \param *pecaOut cópia da peça.

void CopiaPeca(TipoPeca *pecaIn, TipoPeca *pecaOut){
	*pecaOut=*pecaIn;
}

///	Função que retorna a posição vertical da peça
///
///	\param *peca ponteiro para peça.
/// \return um inteiro com a posição vertical da peça.

int PecaGetX(TipoPeca *peca){
	return peca->x;
}

///	Função que retorna a posição horizontal da peça
///
///	\param *peca ponteiro para peça.
/// \return um inteiro com a posição horizontal da peça.

int PecaGetY(TipoPeca *peca){
	return peca->y;
}

///	Função que retorna a velocidade de queda da peça.
///
///	\param *peca ponteiro para peça.
/// \return um inteiro com a velocidade da peça.

int PecaGetSpeed(TipoPeca *peca){
	return peca->speed;
}


///	Função que aloca memória para uma peça.
///
/// \return a nova peça.

TipoPeca *AlocaPeca(){

	TipoPeca *novaPeca = malloc(sizeof(TipoPeca));
	novaPeca-> x = 0;
	novaPeca-> y = 0;
	novaPeca-> speed = 0;
	
	return novaPeca;

}


///	Função que desaloca a memória de uma peça.

void LiberaPeca(TipoPeca* peca){
	free(peca);
}


///	Função que move uma peça verticalmente.
///
///	\param *targetPeca ponteiro para peça.
/// \param inputX nova posição x da peça.

void MovePecaX (TipoPeca *targetPeca, int inputX){
	targetPeca->x=inputX;
}

///	Função que move uma peça horizontalmente.
///
///	\param *targetPeca ponteiro para peça.
/// \param inputY nova posição y da peça.

void MovePecaY (TipoPeca *targetPeca, int inputY){
	targetPeca->y=inputY;
}