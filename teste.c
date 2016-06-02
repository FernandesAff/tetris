#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "engine.h"
#include "pecas.h"

void TesteCorPecaCorFundo (void){
	TipoPeca *peca;
	int resultado=0, i,j;
	peca = AlocaPeca();
	GeraPeca(peca);
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			if(PecaGetBloco(peca,i,j).cor==1)
				resultado=1;
			
	
	CU_ASSERT_FALSE(resultado);
	LiberaPeca(peca);		
}

void TesteCorPecaDiferente (void){
	TipoPeca *peca1, *peca2;
	int resultado=1;
	peca1 = AlocaPeca();
	peca2 = AlocaPeca();
	GeraPeca(peca1);
	GeraPeca(peca2);

	if(PecaGetCor(peca1)==PecaGetCor(peca2))
		resultado=0;

	CU_ASSERT_TRUE(resultado);	
	LiberaPeca(peca1);
	LiberaPeca(peca2);
}


void TestaColisaoParede(void){ // testa colisao quando a peca excede o limite da tela

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao =0;


	CriarTela(tela);
	peca = AlocaPeca();
	GeraPecaEspecifica(peca, 3, 0); // peca de indice 3, rotacao 0

	//colisao à parede esquerda
	MovePecaX (peca, -2); // excede limite à esquerda em 1 unidade (ver peca)
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);
	//colisao à parede direita
	MovePecaX (peca, 22); // excede limite à direita em 1 unidade (ver peca)
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);
	//colisao acima
	MovePecaX (peca, 0); 
	MovePecaY (peca, -2); // excede limite acima em 1 unidade (ver peca)
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);
	//colisao abaixo
	MovePecaX (peca, 0); 
	MovePecaY (peca, 12); // excede limite acima em 1 unidade (ver peca)
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_TRUE(colisao);

	CU_ASSERT_TRUE(colisao);
	//nao colide com nada
	MovePecaX (peca, 0); 
	MovePecaY (peca, 0);
	
	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_FALSE(colisao);
	//fim testes colisao parede

	LiberaPeca(peca);
}


void TestaColisaoBloco(void){ // testa colisao quando um bloco se sobrepoe a outro

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao =0;


	CriarTela(tela);
	peca = AlocaPeca();
	GeraPecaEspecifica(peca, 3, 0); // peca de indice 3, rotacao 0
	
	MovePecaX (peca, 0); 
	MovePecaY (peca, 0);

	AddBloco(peca,tela); //copia a peca pra matriz da tela

	colisao = VerificaColisao(peca, tela); // verifica se a peca colide com a matriz tela (deveria)

	CU_ASSERT_TRUE(colisao);

	MovePecaX (peca, 4); //desloca o bloco para onde nao colide 
	MovePecaY (peca, 0);

	colisao = VerificaColisao(peca, tela); // verifica se a peca colide com a matriz tela (deveria)

	CU_ASSERT_FALSE(colisao);

	LiberaPeca(peca);
}


void TesteLimpaLinha(void){
	TipoTela tela[15][25];
	int resultado=0, i,j,pont=0;

	CriarTela(tela);
	for(i=0;i<25;i++){
		tela[7][i].peca='0';
		tela[7][i].cor=5;
	}

	DeletaLinhas(tela, &pont);

	for(i=0;i<15;i++){
		for(j=0;j<25;j++){
			if(tela[i][j].peca!='-' || tela[i][j].cor!=7){
				resultado=1;
			}
		}	
	}

	CU_ASSERT_FALSE(resultado);	
}


void  AdicionarSuite(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes de datas e nomes",NULL,NULL);
	
	CU_ADD_TEST(suite, TesteCorPecaCorFundo);
	CU_ADD_TEST(suite, TesteCorPecaDiferente);
	CU_ADD_TEST(suite, TesteLimpaLinha);
	CU_ADD_TEST(suite, TestaColisaoParede);
	CU_ADD_TEST(suite, TestaColisaoBloco);
}

int main(){
	
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

   	AdicionarSuite();
	
	CU_basic_set_mode(CU_BRM_VERBOSE);
	
	CU_basic_run_tests();
	
	CU_cleanup_registry();

	return CU_get_error();
}
