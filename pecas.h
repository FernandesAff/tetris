#ifndef PECAS_H
#define PECAS_H

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "tela.h"


typedef struct {
	TipoTela pecas[5];
	int x;
	int y;
	int orient;
} TipoPeca;

TipoPeca *AlocaPeca();
void LiberaPeca(TipoPeca*);

void GeraPeca (TipoPeca *); //gera peca aleatoriamente sobre um dado ponteiro TipoPeca
void MovePecaX (TipoPeca *, int);
void MovePecaY (TipoPeca *, int);
int GetTamanho(TipoPeca);

#endif
