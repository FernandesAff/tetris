///	Gerencia a criação e manipulação da tela.
/// Este módulo implementa a tela do jogo, bem
/// como gerencia as operações relacioanas à ela.
///	
/// \file tela.c
///	\author Anderson, André, Cristóvão, Pedro Vítor.
/// \since 11/04/16
/// \version 2.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "tela.h"
#include "engine.h"

int main () {
	TipoTela tela[15][25];
	
	CriarTela(tela);
	
	Loop(tela);

	return 0;
}
