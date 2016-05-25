#ifndef PECAS_H
#define PECAS_H

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <ncurses.h>
#include "tela.h"

typedef struct TipoPeca TipoPeca;

TipoPeca *AlocaPeca();
void LiberaPeca(TipoPeca*);
void CopiaPeca(TipoPeca*, TipoPeca*);
void GeraPeca (TipoPeca *); //gera peca aleatoriamente sobre um dado ponteiro TipoPeca
void MovePecaX (TipoPeca *, int);
void MovePecaY (TipoPeca *, int);
int PecaGetTamanho(TipoPeca*);
int PecaGetX(TipoPeca*);
int PecaGetY(TipoPeca*);
int PecaGetOrient(TipoPeca*);
TipoTela PecaGetBloco(TipoPeca*, int); //retorna o caractere do bloco na posicao requerida 

#endif
