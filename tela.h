///	Faz a definição do módulo da tela.
/// Define as estruturas do módulo e os
///	protótipos de funções.
///	
/// \file tela.h
///	\author André
/// \since 11/04/16
/// \version 2.3

#ifndef _tela_
#define _tela_
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char peca;
	int cor;
} TipoTela;

void InicioTela();
void CriarTela(TipoTela [][25]);
void MostrarTela(TipoTela [][25], int, int);
void SetPecaCor(TipoTela*,int);  // atribui cor à peca
void SetPecaCaractere(TipoTela*,char); // atribui o caractere à peca
void SetPeca(TipoTela*, char, int); //atribui a cor e o caractere
void FimTela(int);
int VerificaSeBloco(TipoTela); //retorna 1 se ha bloco, 0 se nao.


#endif
