#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char peca;
	int cor;
} TipoTela;

void criar_tela(TipoTela [][25]);
void mostrar_tela(TipoTela [][25], int);