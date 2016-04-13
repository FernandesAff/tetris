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

void gera_peca (TipoPeca *); //gera peca aleatoriamente sobre um dado ponteiro TipoPeca
void move_peca_x (TipoPeca *, int);
void move_peca_y (TipoPeca *, int);
