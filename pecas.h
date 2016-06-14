///	Faz a definição do módulo de peças.
/// Define as estruturas do módulo e os protótipos
/// de funções.
///	
/// \file pecas.h
///	\author Anderson
/// \since 11/04/16
/// \version 2.6

#ifndef PECAS_H
#define PECAS_H

#define TAMANHO_X 5
#define TAMANHO_Y 5

#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>       
#include <ncurses.h>
#include "tela.h"

typedef struct{
	TipoTela pecas[TAMANHO_Y][TAMANHO_X];
	int x;
	int y;
	int speed;
} TipoPeca;

TipoPeca *AlocaPeca();
void LiberaPeca(TipoPeca*);
void CopiaPeca(TipoPeca*, TipoPeca*);
void GeraPeca (TipoPeca *);
void GeraPecaEspecifica(TipoPeca *, int, int);
void MovePecaX (TipoPeca *, int);
void MovePecaY (TipoPeca *, int);
void RotacionaPeca(TipoPeca*);
void SpeedUp(TipoPeca *, int);
int PecaGetCor(TipoPeca*);
int PecaGetX(TipoPeca*);
int PecaGetY(TipoPeca*);
int PecaGetSpeed(TipoPeca*);
TipoTela PecaGetBloco(TipoPeca*, int, int);

#endif
