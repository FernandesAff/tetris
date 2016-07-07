///	Implementa a instrumentação do módulo peças.
/// Garante a validade das entradas e saídas do
/// módulo peças.
///	
/// \file pecas_inst.c
///	\author Cristóvão
/// \since 05/07/16
/// \version 1.1

#include <assert.h>
#include "pecas.h"
#include <time.h>

void MovePecaXInst (TipoPeca *peca, int x){
	//assertiva de entrada
	assert(peca!=NULL);
	MovePecaX(peca ,x);
	//assertiva de saida
	assert(peca!=NULL);
}

void MovePecaYInst (TipoPeca *peca, int y){
	//assertiva de entrada
	assert(peca!=NULL);
	MovePecaY(peca ,y);
	//assertiva de saida
	assert(peca!=NULL);
}

TipoPeca* AlocaPecaInst(){
	TipoPeca *peca = NULL;
	peca = AlocaPeca();
	//assertiva de saida
	assert(peca != NULL);
	return peca;
}

void LiberaPecaInst(TipoPeca* peca){
	//assertiva de entrada
	assert(peca!=NULL);
	LiberaPeca(peca);
}

void CopiaPecaInst(TipoPeca* a, TipoPeca* b){
	//assertiva de entrada
	assert(a != NULL);
	CopiaPeca(a,b);
	//assertiva de saida
	assert(a != NULL && b!= NULL);
}

void GeraPecaInst (TipoPeca *peca){
	GeraPeca (peca);
	//assertiva de saida
	assert(peca != NULL);
}

void RotacionaPecaInst(TipoPeca* peca){
	//assertiva de entrada
	assert(peca != NULL);
	RotacionaPeca(peca);
	//assertiva de saida
	assert(peca != NULL);
}

void SpeedUpInst(TipoPeca *peca, int valor){
	//assertiva de entrada
	assert(peca != NULL);
	SpeedUp(peca,valor);
	//assertivas de saida
	assert(peca != NULL);
	assert(peca->speed <50);
	
}