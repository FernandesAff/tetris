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