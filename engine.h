///	Contém a definição do módulo engine.
/// Define os protótipos das funções do 
/// módulo.
///	
/// \file engine.h
///	\author Cristóvão
/// \since 11/04/16
/// \version 2.8

#define TAMANHOTELAY 15
#define TAMANHOTELAX 25 
#include <ncurses.h>
#include "tela.h"
#include "pecas.h"

int VerificaMorte(TipoTela [][TAMANHOTELAX]);
int VerificaColisao(TipoPeca *, TipoTela [][TAMANHOTELAX]);
void PoePecaNoTopo(TipoPeca *, TipoTela [][TAMANHOTELAX]);
void DeletaBloco(TipoTela *);
void AddBloco(TipoPeca *,TipoTela [][TAMANHOTELAX]);
void RemoveBloco(TipoPeca *,TipoTela [][TAMANHOTELAX]);
int VerificaLinhas(TipoTela [][TAMANHOTELAX]);
void Gravidade(TipoTela [][TAMANHOTELAX],int);
void DeletaLinhas(TipoTela [][TAMANHOTELAX],int *);
int PegaInput();
int Loop (TipoTela [][TAMANHOTELAX]);
