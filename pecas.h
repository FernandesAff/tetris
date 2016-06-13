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
void GeraPecaEspecifica(TipoPeca *, int, int); //gera peca especifica, para teste 
void MovePecaX (TipoPeca *, int);
void MovePecaY (TipoPeca *, int);
void RotacionaPeca(TipoPeca*);
void SpeedUp(TipoPeca *, int);
int PecaGetCor(TipoPeca*);
int PecaGetX(TipoPeca*);
int PecaGetY(TipoPeca*);
int PecaGetSpeed(TipoPeca*);
TipoTela PecaGetBloco(TipoPeca*, int, int); //retorna o caractere do bloco na posicao requerida (x,y)

#endif
