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
void set_peca_cor(TipoTela*,int);  // atribui cor à peca
void set_peca_caractere(TipoTela*,char); // atribui o caractere à peca
void set_peca(TipoTela*, char, int); //atribui a cor e o caractere
void fim_tela(int);
int verifica_se_bloco(TipoTela); //retorna 1 se ha bloco, 0 se nao.


#endif
