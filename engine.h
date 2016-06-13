#define TAMANHOTELAY 15
#define TAMANHOTELAX 25
#include <ncurses.h>
#include "tela.h"
#include "pecas.h"

int VerificaMorte(TipoTela [][25]);
int VerificaColisao(TipoPeca *, TipoTela [][25]);
void PoePecaNoTopo(TipoPeca *, TipoTela [][25]);
void DeletaBloco(TipoTela *);
void AddBloco(TipoPeca *,TipoTela [][25]);
void RemoveBloco(TipoPeca *,TipoTela [][25]);
int VerificaLinhas(TipoTela [][TAMANHOTELAX]);
void Gravidade(TipoTela [][TAMANHOTELAX],int);
void DeletaLinhas(TipoTela [][TAMANHOTELAX],int *);
int PegaInput();
int Loop (TipoTela [][25]);
