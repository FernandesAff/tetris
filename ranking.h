///	Define o módulo do placar do jogo
/// Este módulo define as estruturas do
/// módulo e os protótipos de funções.
///	
/// \file ranking.h
///	\author André
/// \since 11/04/16
/// \version 2.1

#define ARQUIVO "ranking.txt"
#define AUX "aux.txt"
#include <stdio.h>

typedef struct {
	char apelido[7];
	int pontos;
	int dia;
	int mes;
	int ano;
	int tempo;

} TipoJogador;

int* ReceberApelido ();
void ConverterApelido(int *, TipoJogador *);
void ReceberData(TipoJogador *);
int VerificaPlacar();
void CriaPlacar (TipoJogador);
void AtualizaPlacar (TipoJogador);