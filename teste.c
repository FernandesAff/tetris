#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h" 
#include "engine.h"
#include "pecas.h"

void TesteAlocaPeca (void){
	int flagNulo = 0;
	TipoPeca *peca;
	peca = AlocaPeca();
	if (peca == NULL) flagNulo = 1;
	CU_ASSERT_FALSE(flagNulo);

	LiberaPeca(peca);
}

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


void TestaMorte(void){
	int morte = 0,
	    i = 0;
	
	TipoTela tela[15][25];
	TipoTela bloco,
		 vazio;
	bloco.cor = 5;
	bloco.peca = '0';
	vazio.cor = 7;
	vazio.peca = '-';

	CriarTela(tela);

	morte = VerificaMorte(tela);
	
	CU_ASSERT_FALSE(morte);

	//completa uma fileira de blocos até antes da linha de morte 
	for(i=15; i>5; i--) 
		tela[i][14] = bloco;

	//testa se, para cada posicao de morte, a funcao retorna a morte
	for(i=0; i<25; i++){
		tela[5][i] = bloco;
		morte = VerificaMorte(tela);
		CU_ASSERT_TRUE(morte);
		tela[5][i] = vazio;
		}	

	//nao deve alertar morte, pois fileira [5][i] está vazia.
	morte = VerificaMorte(tela);

	CU_ASSERT_FALSE(morte); 

}


void TestaColisaoParede(void){ // testa colisao quando a peca excede o limite da tela

	TipoTela tela[15][25] ;
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
	MovePecaY (peca, 12); // excede limite abaixo em 1 unidade (ver peca)
	
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


// testa colisao da peca com os blocos da tela
void TestaColisaoBloco(void){ 

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao =0;


	CriarTela(tela);
	peca = AlocaPeca();
	GeraPecaEspecifica(peca, 3, 0); // peca de indice 3, rotacao 0
	
	MovePecaX (peca, 0); 
	MovePecaY (peca, 0);

	//copia a peca pra matriz da tela
	AddBloco(peca,tela); 

	// verifica se a peca colide com a matriz tela (deveria)
	colisao = VerificaColisao(peca, tela); 

	CU_ASSERT_TRUE(colisao);

	//desloca o bloco para onde nao colide 
	MovePecaX (peca, 4); 

	colisao = VerificaColisao(peca, tela);

	CU_ASSERT_FALSE(colisao);

	LiberaPeca(peca);
}


void TesteLimpaLinha(void){
	TipoTela tela[15][25];
	int resultado = 0, 
	    i = 0,
	    j = 0,
	    pont = 0;

	CriarTela(tela);
	for(j=0;j<15;j++){
		for(i=0;i<25;i++){
			tela[7][i].peca='0';
			tela[7][i].cor=5;
		}
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

void TestaPecaNoTopo(void){

	TipoTela tela[15][25];
	TipoPeca *peca;
	int colisao = 0,
	    i;

	CriarTela(tela);
	peca = AlocaPeca();
	GeraPeca(peca);
	MovePecaX(peca, 10);
	MovePecaY(peca, 10);
	
	PoePecaNoTopo(peca,tela);
	
	// A peça nao deve ultrapassar os limites da tela
	colisao = VerificaColisao(peca,tela);

	CU_ASSERT_FALSE(colisao);

	// Aplica a peça à tela
	AddBloco(peca, tela);

	colisao = 0;

	//deve haver pelo menos um bloco na posicao [0][i]
	for(i=0; i<25; i++){
		if (VerificaSeBloco(tela[0][i])) colisao = 1;
	}

	CU_ASSERT_TRUE(colisao);

}

void  AdicionarSuite(void){
	CU_pSuite suite;
	
	suite = CU_add_suite("Testes de datas e nomes",NULL,NULL);

	CU_ADD_TEST(suite, TesteAlocaPeca);	
	CU_ADD_TEST(suite, TesteCorPecaCorFundo);
	CU_ADD_TEST(suite, TesteCorPecaDiferente);
	CU_ADD_TEST(suite, TesteLimpaLinha);
	CU_ADD_TEST(suite, TestaColisaoParede);
	CU_ADD_TEST(suite, TestaColisaoBloco);
	CU_ADD_TEST(suite, TestaPecaNoTopo);

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
