#ifndef _tela_
#define _tela_


#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char peca;
	int cor;
} TipoTela;

void inicio_tela();
void criar_tela(TipoTela [][25]);
void mostrar_tela(TipoTela [][25], int);
void fim_tela(int);

#endif
