#define TAMANHOTELAY 15
#define TAMANHOTELAX 25 
#include <ncurses.h>
#include "tela.h"
#include "peças.h"

int verificamorte(TipoTela [][25]);
int verifica_colisao(TipoPeca *, TipoTela [][25]);
void deletabloco(TipoTela *);
void addbloco(TipoPeca *,TipoTela [][25]);
void removebloco(TipoPeca *,TipoTela [][25]);
int verificalinhas(TipoTela [][TAMANHOTELAX]);
void gravidade(TipoTela [][TAMANHOTELAX],int);
void deletalinhas(TipoTela [][TAMANHOTELAX],int *);
int pega_input();
int loop (TipoTela [][25]);
